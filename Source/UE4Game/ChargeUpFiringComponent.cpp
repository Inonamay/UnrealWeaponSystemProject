#include "ChargeUpFiringComponent.h"

UChargeUpFiringComponent::UChargeUpFiringComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UChargeUpFiringComponent::BeginPlay()
{
	Super::BeginPlay();

	EventManager->OnFirePressed.AddDynamic(this, &UChargeUpFiringComponent::OnFirePressed);
	EventManager->OnFireReleased.AddDynamic(this, &UChargeUpFiringComponent::OnFireReleased);
	WeaponActor = Cast<AWeaponBase>(GetOwner());
	ChargeUpAccu = 0;
	FireAccu = FireCooldown;
}


void UChargeUpFiringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FireAccu += DeltaTime;
	if (FireState)
	{
		ChargeUpAccu += DeltaTime;
		if (ChargeUpAccu >= ChargeUpMax)
		{
			WeaponActor->ComponentRequestFire(ChargeUpAccu);
			ChargeUpAccu = 0;
			FireState = false;
		}
	}
}

void UChargeUpFiringComponent::OnFirePressed()
{
	if (!FireState && FireAccu >= FireCooldown)
	{
		FireState = true;
		FireAccu = 0;
	}
}

void UChargeUpFiringComponent::OnFireReleased()
{
	if (FireState)
	{
		FireState = false;
		WeaponActor->ComponentRequestFire(ChargeUpAccu);
		ChargeUpAccu = 0;
	}
}

