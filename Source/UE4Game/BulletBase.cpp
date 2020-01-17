
#include "BulletBase.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "DamageableComponent.h"
ABulletBase::ABulletBase()
{
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
}

UStaticMeshComponent* ABulletBase::GetProjectileMesh()
{
	return ProjectileMesh;
}


void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
	Launch();

}

void ABulletBase::CreateDebugLocator(FVector Location)
{
	if (DebugLocator)
	{
		const FRotator SpawnRotation = { 0,0,0 };
		const FVector SpawnLocation = Location;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AHitLocator>(DebugLocator, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

void ABulletBase::CreateDebugLocator(FVector Location, AActor* AttachmentActor)
{
	if (DebugLocator)
	{
		const FRotator SpawnRotation = { 0,0,0 };
		const FVector SpawnLocation = Location;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AHitLocator>(DebugLocator, SpawnLocation, SpawnRotation, ActorSpawnParams)->AttachToActor(AttachmentActor, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ABulletBase::Launch()
{
	if (ProjectileMesh->GetStaticMesh())
	{
		ProjectileMesh->SetSimulatePhysics(true);
		ProjectileMesh->SetWorldRotation(GetActorRotation());
		ProjectileMesh->SetWorldLocation(GetActorLocation());
		ProjectileMesh->SetEnableGravity(Gravity);
		FVector LaunchDirection = ProjectileMesh->GetRightVector() * Force;
		ProjectileMesh->AddImpulse(LaunchDirection, NAME_None, true);
		ProjectileMesh->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
	}
}

void ABulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	CreateDebugLocator(Hit.Location, OtherActor);
	UDamageableComponent* other = Hit.Actor->FindComponentByClass<UDamageableComponent>();
	if (other) other->Damage(HitDamage);
	HitsBeforeDestroyed--;
	if (HitsBeforeDestroyed < 1 && HitsBeforeDestroyed > -1)
	{
		SetLifeSpan(TimeAliveAfterBounces);
		ProjectileMesh->SetSimulatePhysics(!StopsMovingAfterCollision);
	}
}
