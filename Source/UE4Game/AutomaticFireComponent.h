// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EventActorComponent.h"
#include "WeaponBase.h"
#include "AutomaticFireComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UAutomaticFireComponent : public UEventActorComponent
{
	GENERATED_BODY()

public:	
	UAutomaticFireComponent();

protected:
	virtual void BeginPlay() override;

	AWeaponBase* WeaponActor;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Fire Rate")
	float FireRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Fire Cooldown")
	float FireCooldown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Fire Mode")
	float TriggerPower = 1.0f;

	float FireCooldownAccu;
	float FireRateAccu;
private:
	bool FireState;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon Event")
	void OnFireEvent();

	UFUNCTION(BlueprintCallable, Category = "Weapon Event")
	void OnStopFiringEvent();
};
