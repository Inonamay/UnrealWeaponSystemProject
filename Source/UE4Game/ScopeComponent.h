// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.h"
#include "ScopeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UScopeComponent : public UAimingComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScopeComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scope")
		float ZoomAmount = 2.0f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void Aim() override;
	void UnAim() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
