
#include "AutomaticFireComponent.h"

UAutomaticFireComponent::UAutomaticFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	FireState = false;
}

void UAutomaticFireComponent::BeginPlay()
{
	Super::BeginPlay();
	EventManager->OnFirePressed.AddDynamic(this, &UAutomaticFireComponent::OnFireEvent);
	EventManager->OnFireReleased.AddDynamic(this, &UAutomaticFireComponent::OnStopFiringEvent);
	FireCooldownAccu = FireCooldown;
	WeaponActor = Cast<AWeaponBase>(GetOwner());
}


void UAutomaticFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	FireRateAccu += DeltaTime;
	FireCooldownAccu += DeltaTime;
	if (FireState)
	{
		if (FireRate <= FireRateAccu)
		{
			if (!WeaponActor->ComponentRequestFire(TriggerPower))
			{
				FireState = false;
				EventManager->OnTriggerReleased.Broadcast();
			}
			FireRateAccu = 0;
		}
	}
}

void UAutomaticFireComponent::OnFireEvent()
{
	if (FireCooldownAccu >= FireCooldown)
	{
		FireState = true;
		FireCooldownAccu = 0;
	}
}

void UAutomaticFireComponent::OnStopFiringEvent()
{
	if (FireState)
	{
		FireState = false;
		EventManager->OnTriggerReleased.Broadcast();
		FireRateAccu = 0;
	}
}

