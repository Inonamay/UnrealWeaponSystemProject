	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UsableInterface.h"
#include "PlayerCharacter.h"
#include "BulletBase.h"
#include "AmmoComponent.h"
#include "EventManagerComponent.h"
#include "Interactable_Interface.h"
#include "WeaponBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickedUp);
class AUE4GameCharacter;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UE4GAME_API AWeaponBase : public AActor, public IInteractable_Interface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)         
	class USkeletalMeshComponent* Gun;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UParticleSystemComponent* OnFireEffect;

public:	
	AWeaponBase();
	UPROPERTY()
	FPickedUp PickedUp;

protected:
	virtual void BeginPlay() override;
	bool IsBulletSpreadSet = false;
	FVector BulletSpreadDirection = { 0, 0, 0 };
	bool IsWeaponFireSuccess = false;
public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Weapon Event")
	UEventManagerComponent* EventManager;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Ammo")
	UAmmoComponent* AmmoComponent;
	
	virtual void Interact_Implementation(ACharacter* PickupActor) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UE4 Character")
	AUE4GameCharacter* OwningPlayer;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnStopFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool ComponentRequestFire(float Power);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnTriggerReleased();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ShootRequestResult(bool Value);

	UFUNCTION()
	void SetBulletSpreadDirection(FVector Direction);

	void SuccessfulFire(float Power);
};
