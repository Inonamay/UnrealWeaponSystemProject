#include "AmmoComponent.h"
#include "DrawDebugHelpers.h"
#include "WeaponBase.h"

void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
	EventManager->OnWeaponShoot.AddDynamic(this, &UAmmoComponent::OnFire);
	EventManager->OnWeaponShootSuccessful.AddDynamic(this, &UAmmoComponent::OnFireSuccess);
}

void UAmmoComponent::OnFire()
{
	if (TestAmmo())
	{
		EventDispatch(true);
	}
	else
	{
		EventDispatch(false);
	}
}

void UAmmoComponent::OnFireSuccess()
{
	UseAmmo();
}

int UAmmoComponent::Reload(int AvailableAmmo, int BulletIndex)
{
	if (Validate(BulletIndex))
	{
		int previousAmmo = Magazines[BulletIndex].LoadedAmmo;
		Magazines[BulletIndex].LoadedAmmo += AvailableAmmo;
		if (Magazines[BulletIndex].LoadedAmmo > Magazines[BulletIndex].MagazineSize) 
		{
			Magazines[BulletIndex].LoadedAmmo = Magazines[BulletIndex].MagazineSize;
		}
		AvailableAmmo -= (Magazines[BulletIndex].LoadedAmmo - previousAmmo);
	}
	return AvailableAmmo;
}

bool UAmmoComponent::UseAmmoAndGetRemaining(int BulletIndex, int UseCount, int& RemainingAmmo)
{
	if (Validate(BulletIndex))
	{
		bool AmmoUseSuccessful = UseAmmoImpl(BulletIndex, UseCount);
		RemainingAmmo = Magazines[BulletIndex].LoadedAmmo;
		return AmmoUseSuccessful;
	}
	return false;
}

TSubclassOf<class ABulletBase> UAmmoComponent::GetCurrentAmmo(int BulletIndex)
{
	return Magazines[BulletIndex].bulletType;
}

bool UAmmoComponent::UseAmmo()
{
	if (Validate(CurrentAmmo))
	{
		return UseAmmoImpl(CurrentAmmo, NumberOfAmmoToUse);
	}
	return false;
}

bool UAmmoComponent::TestAmmo(int BulletIndex, int UseCount)
{
	if (Validate(BulletIndex))
	{
		return Magazines[BulletIndex].LoadedAmmo >= UseCount;
	}
	return false;
}

void UAmmoComponent::SetCurrentAmmoIndex(int index)
{
	if (Validate(index)) { CurrentAmmo = index; }
	else 
	{ UE_LOG(LogTemp, Warning, TEXT("Could not change to ammo type because it did not exist!")); }
}

bool UAmmoComponent::UseAmmoImpl(int BulletIndex, int UseCount)
{
	if (Magazines[BulletIndex].LoadedAmmo >= UseCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::FromInt(Magazines[BulletIndex].LoadedAmmo));
		Magazines[BulletIndex].LoadedAmmo -= UseCount;
		return true;
	}
	return false;
}

bool UAmmoComponent::Validate(int BulletIndex)
{
	if (BulletIndex >= 0)
	{
		return BulletIndex < Magazines.Num();
	}
	return false;
}

void UAmmoComponent::EventDispatch(bool Result)
{
	if (auto ThisWeapon = Cast<AWeaponBase>(GetOwner()))
	{
		ThisWeapon->ShootRequestResult(Result);
		if (Result)
		{
			EventManager->OnAmmoCheckSuccess.Broadcast();
		}
		else
		{
			EventManager->OnAmmoCheckFail.Broadcast();
		}
	}
}

