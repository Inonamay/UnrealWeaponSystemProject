// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.h"
#include "AimDownSightsComponent.generated.h"

class AWeaponBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UAimDownSightsComponent : public UAimingComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimDownSightsComponent();
	AWeaponBase* owner;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aim")
	FVector Location = {0,0,0};
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aim")
	FRotator Rotation = { 0,0,0 };
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aim")
		float TimeToFullyAimed = 0.1f;
	float timer = 0;
	void Aim() override;
	void UnAim() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
