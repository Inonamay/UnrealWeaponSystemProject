// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageable_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE4GAME_API IDamageable_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Damage(int amount);
	virtual void Damage_Implementation(int amount) {}
};
