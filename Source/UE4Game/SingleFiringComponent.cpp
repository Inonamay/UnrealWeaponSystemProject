#include "SingleFiringComponent.h"

USingleFiringComponent::USingleFiringComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USingleFiringComponent::BeginPlay()
{
	Super::BeginPlay();

	EventManager->OnFirePressed.AddDynamic(this, &USingleFiringComponent::OnFirePressed);
	EventManager->OnFireReleased.AddDynamic(this, &USingleFiringComponent::OnFireReleased);
	WeaponActor = Cast<AWeaponBase>(GetOwner());
	
}

void USingleFiringComponent::OnFirePressed()
{
	if (!FireState && FireCooldownAccu < 0)
	{
		FireState = true;
		FireCooldownAccu = FireCooldown;
		WeaponActor->ComponentRequestFire(TriggerPower);
		EventManager->OnTriggerReleased.Broadcast();
	}
}

void USingleFiringComponent::OnFireReleased()
{
	FireState = false;
}

void USingleFiringComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FireCooldownAccu -= DeltaTime;
}
