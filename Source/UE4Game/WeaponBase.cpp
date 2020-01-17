// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "UE4GameCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	EventManager = CreateDefaultSubobject<UEventManagerComponent>(FName("EventManager"));
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Gun Mesh")); 
	OnFireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Muzzle Flash"));
	OnFireEffect->AttachToComponent(Gun, FAttachmentTransformRules::SnapToTargetIncludingScale, "Muzzle");
	OnFireEffect->SetWorldLocation(Gun->GetSocketLocation("Muzzle"));
	OnFireEffect->Deactivate();

}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	OnFireEffect->Deactivate();
	AmmoComponent = Cast<UAmmoComponent>(this->GetComponentByClass(UAmmoComponent::StaticClass()));
}

void AWeaponBase::Interact_Implementation(ACharacter* PickupActor)
{
	OwningPlayer = Cast<AUE4GameCharacter>(PickupActor);
	if (OwningPlayer) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (TEXT("I, %s am picked up!"), GetName()));
		Gun->SetSimulatePhysics(false);
		OwningPlayer->EquipWeapon(this);
		Gun->SetCollisionProfileName(TEXT("NoCollision"));
		if (PickedUp.IsBound()) //<~~~~
		{
			PickedUp.Broadcast();
		}
	}
}

void AWeaponBase::OnFire()
{
	OnFireEffect->Activate();
	EventManager->OnFirePressed.Broadcast();
}

void AWeaponBase::OnStopFire()
{
	OnFireEffect->Deactivate();
	EventManager->OnFireReleased.Broadcast();
}

bool AWeaponBase::ComponentRequestFire(float Power)
{
	IsWeaponFireSuccess = true;
	EventManager->OnWeaponShoot.Broadcast();
	if (IsWeaponFireSuccess)
	{
		if (EventManager->OnWeaponShootPrimeProjectile.IsBound())
		{
			UE_LOG(LogTemp, Warning, TEXT("Right Place!"));

			EventManager->OnWeaponShootPrimeProjectile.Broadcast(BulletSpreadDirection, Power);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Should Not be here dude!"));

			SuccessfulFire(Power);
		}
		return true;
	}
	return false;
}

void AWeaponBase::OnTriggerReleased()
{

}

void AWeaponBase::ShootRequestResult(bool Value)
{
	if (!Value)
	{
		IsWeaponFireSuccess = Value;
	}
}

void AWeaponBase::SetBulletSpreadDirection(FVector Direction)
{
	IsBulletSpreadSet = true;
	BulletSpreadDirection = Direction;
}

void AWeaponBase::SuccessfulFire(float Power)
{
	const FRotator SpawnRotation = Gun->GetComponentRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = Gun->GetSocketLocation("Muzzle") + Gun->GetRightVector() * 100; /*+ SpawnRotation.RotateVector(GunOffset)*/;
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (AmmoComponent)
	{
		GetWorld()->SpawnActor<ABulletBase>(AmmoComponent->GetCurrentAmmo(), SpawnLocation, SpawnRotation, ActorSpawnParams);
	}

	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Yellow, FString::SanitizeFloat(Power));


	const int RayLength = 1000;
	FVector StartLocation = Gun->GetSocketLocation(FName("Muzzle"));
	FVector EndLocation = StartLocation;
	if (IsBulletSpreadSet)
	{
		EndLocation += BulletSpreadDirection * RayLength;
	}
	else
	{
		EndLocation += GetActorRightVector() * RayLength;
	}
//	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1.0f, 0, 3);

	EventManager->OnWeaponShootSuccessful.Broadcast();
}
