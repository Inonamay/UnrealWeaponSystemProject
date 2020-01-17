// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageableComponent();
	UFUNCTION(BlueprintCallable)
		void Damage(int amount);
	virtual void Damage_Implementation(int amount) {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		int HitPoints = 10;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		
};
