// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EventManagerComponent.h"
#include "EventActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UE4GAME_API UEventActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEventActorComponent();

	UPROPERTY(BlueprintReadWrite, Category = "Event Manager")
	UEventManagerComponent* EventManager;

	UFUNCTION(BlueprintCallable, Category = "Event Actor Component")
	void Initialize();

protected:
	virtual void BeginPlay() override;

};
