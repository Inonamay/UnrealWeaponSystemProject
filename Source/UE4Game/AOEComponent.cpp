// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEComponent.h"
#include "BulletBase.h"
#include "DamageableComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values for this component's properties
UAOEComponent::UAOEComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UAOEComponent::BeginPlay()
{
	Super::BeginPlay();
	ComponentRef = GetAreaComponent();
	if (bTriggersOnImpact) 
	{
		ABulletBase* OwningBullet = Cast<ABulletBase>(GetOwner());
		if (OwningBullet) 
		{
			OwningBullet->GetProjectileMesh()->OnComponentHit.AddDynamic(this, &UAOEComponent::Impact);
		}
	}
	if(bTickableDamage) GetOwner()->GetWorldTimerManager().SetTimer(TickDamageTimerHandle, this, &UAOEComponent::DamageTick, TickRate, true);
	ComponentRef->SetGenerateOverlapEvents(!bTriggersOnImpact);
	ComponentRef->OnComponentBeginOverlap.AddDynamic(this, &UAOEComponent::OnOverlap);
	// ...
	
}

UBoxComponent* UAOEComponent::GetAreaComponent()
{
	UBoxComponent* options = GetOwner()->FindComponentByClass<UBoxComponent>();
	return options;
}

void UAOEComponent::DamageTick()
{
	TArray<AActor*> actors;
	ComponentRef->GetOverlappingActors(actors);
	for (auto actor : actors)
	{
		UDamageableComponent* Damageable = actor->FindComponentByClass<UDamageableComponent>();
		if (Damageable) Damageable->Damage(OverlapDamage);
	}
}

void UAOEComponent::Impact(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ComponentRef)
	{
		ComponentRef->SetGenerateOverlapEvents(true);
	}
}

void UAOEComponent::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UDamageableComponent* other = OtherActor->FindComponentByClass<UDamageableComponent>();
	if (other)
	{
		other->Damage(OverlapDamage);
	}
}

