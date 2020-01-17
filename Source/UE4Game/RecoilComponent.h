// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EventActorComponent.h"
#include "RecoilComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API URecoilComponent : public UEventActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoilComponent();
	AController* OwnerController;

	int Counter = 0;
	float Punch = 0;
	float MaxPunch = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
	float Strength = 0.1f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION()
		void OnTriggerRelease();
	
	UFUNCTION()
	void RecoilFunction();

};
