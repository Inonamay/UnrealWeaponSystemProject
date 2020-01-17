#include "BurstFireComponent.h"

UBurstFireComponent::UBurstFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}

void UBurstFireComponent::BeginPlay()
{
	Super::BeginPlay();

	WeaponActor = Cast<AWeaponBase>(GetOwner());
	EventManager->OnFirePressed.AddDynamic(this, &UBurstFireComponent::OnProjectilePrime);
}

void UBurstFireComponent::OnProjectilePrime()
{
	for (int i = 0; i < 5; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Yo!"))
		WeaponActor->ComponentRequestFire(1.0f);
	}
}
