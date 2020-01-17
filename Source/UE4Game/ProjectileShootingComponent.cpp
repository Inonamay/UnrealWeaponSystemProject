
#include "ProjectileShootingComponent.h"
#include "AmmoComponent.h"
#include "BulletBase.h"
#include "DrawDebugHelpers.h"
#include "DamageableComponent.h"
#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"

UProjectileShootingComponent::UProjectileShootingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UProjectileShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	EventManager->OnWeaponShootPrimeProjectile.AddDynamic(this, &UProjectileShootingComponent::SpawnProjectile);
}

void UProjectileShootingComponent::SpawnProjectile(FVector BulletSpreadDir, float Strength)
{	
	USkeletalMeshComponent* Gun = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	const FRotator SpawnRotation = Gun->GetComponentRotation();
	const FVector SpawnLocation = Gun->GetSocketLocation("Muzzle") + GetOwner()->GetActorRightVector() * 250;
	if (Bullet.BulletType == FBulletType::HitScan)
	{
		TArray<FHitResult> Hits;
		FVector StartLocation = SpawnLocation;
		FVector EndLocation = StartLocation + GetOwner()->GetActorRightVector() * Bullet.Range;
		FCollisionQueryParams CollisionParameters(FName(TEXT("Bullet Hitscan")), false, GetOwner());
		CollisionParameters.bTraceComplex = true;
		CollisionParameters.bFindInitialOverlaps =false;

		FCollisionObjectQueryParams Params;
		Params.AddObjectTypesToQuery(ECC_Pawn);
		Params.AddObjectTypesToQuery(ECC_WorldStatic);
		Params.AddObjectTypesToQuery(ECC_WorldDynamic);
		//TODO: FIX THIS
		//EWWW
		GetWorld()->LineTraceMultiByObjectType(Hits, StartLocation, EndLocation, Params, CollisionParameters);
		//GetWorld()->LineTraceMultiByChannel(Hits, StartLocation, EndLocation, ECollisionChannel::ECC_Pawn, CollisionParameters);
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 2, 5, 1.f);
		for (int i = 0; i < Hits.Num(); i++)
		{
			if (Hits[i].Actor != nullptr)
			{
				FVector UnrealsMethodForNormalizingVectorsIsStupid = StartLocation - Hits[i].Location;
				UnrealsMethodForNormalizingVectorsIsStupid.Normalize();
				CreateDebugLocator(Hits[i].Location + UnrealsMethodForNormalizingVectorsIsStupid, Hits[i].GetActor());
				UDamageableComponent* other = Cast<UDamageableComponent>(Hits[i].Actor->GetComponentByClass(UDamageableComponent::StaticClass()));
				if (other)
				{
					UE_LOG(LogTemp, Warning, TEXT("YOYOYOYOY"))
					other->Damage(Bullet.HitDamage);
				}
			}
		}

	}
	else
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GEngine->AddOnScreenDebugMessage(0, 3, FColor::Yellow, FString::SanitizeFloat(Strength));
		GetWorld()->SpawnActor<ABulletBase>(Bullet.BulletReference, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}

	EventManager->OnWeaponShootSuccessful.Broadcast();
}

void UProjectileShootingComponent::CreateDebugLocator(FVector Location)
{
	//if (DebugLocator)
	//{
	//	const FRotator SpawnRotation = { 0,0,0 };
	//	const FVector SpawnLocation = Location;
	//	FActorSpawnParameters ActorSpawnParams;
	//	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//	GetWorld()->SpawnActor<AHitLocator>(DebugLocator, SpawnLocation, SpawnRotation, ActorSpawnParams);
	//}
}

void UProjectileShootingComponent::CreateDebugLocator(FVector Location, AActor* AttachmentActor)
{
	//if (DebugLocator)
	//{
	//	const FRotator SpawnRotation = { 0,0,0 };
	//	const FVector SpawnLocation = Location;
	//	FActorSpawnParameters ActorSpawnParams;
	//	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//	GetWorld()->SpawnActor<AHitLocator>(DebugLocator, SpawnLocation, SpawnRotation, ActorSpawnParams)->AttachToActor(AttachmentActor, FAttachmentTransformRules::KeepWorldTransform);

	//}
}