// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "ChargeUpFiringComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UChargeUpFiringComponent : public UEventActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChargeUpFiringComponent();

	AWeaponBase* WeaponActor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fire Mode")
	float ChargeUpMax;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fire Mode")
	float FireCooldown;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fire Mode")
	bool FireState = false;

	float ChargeUpAccu = 0;
	float FireAccu = 0;
	
	UFUNCTION(Category = "Fire Mode")
	void OnFirePressed();

	UFUNCTION(Category = "Fire Mode")
	void OnFireReleased();
};
