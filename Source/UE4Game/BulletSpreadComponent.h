// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventActorComponent.h"
#include "WeaponBase.h"
#include "BulletSpreadComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UE4GAME_API UBulletSpreadComponent : public UEventActorComponent
{
	GENERATED_BODY()

public:	
	UBulletSpreadComponent();

protected:
	virtual void BeginPlay() override;
	AWeaponBase* WeaponActor;
public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet Spread")
	float BulletSpreadDegrees = 10;

	UFUNCTION(BlueprintNativeEvent, Category = "Bullet Spread")
	FVector BulletSpreadFunction();

	UFUNCTION()
	void OnWeaponShoot();

};
