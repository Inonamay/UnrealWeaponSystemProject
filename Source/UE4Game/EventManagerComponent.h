// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EventManagerComponent.generated.h"
typedef int EventHashId;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileSpawnEvent, FVector, BulletSpreadDir, float, Strength);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class UE4GAME_API UEventManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnFirePressed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnFireReleased;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnAmmoCheckSuccess;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnAmmoCheckFail;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnScopePressed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnScopeReleased;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnWeaponShootSuccessful;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnWeaponShoot;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FProjectileSpawnEvent OnWeaponShootPrimeProjectile;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Weapon Events")
	FWeaponEvent OnTriggerReleased;


};
