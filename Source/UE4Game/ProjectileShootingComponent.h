// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventActorComponent.h"
#include "BulletBase.h"
#include "ProjectileShootingComponent.generated.h"

UENUM(BlueprintType)
enum FBulletType
{
	HitScan, 
	Solid
};

USTRUCT(BlueprintType, Blueprintable)
struct FBullet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet")
	TEnumAsByte<FBulletType> BulletType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet")
	int Count;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet")
	float Range;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet")
	TSubclassOf<class ABulletBase> BulletReference;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bullet")
	float HitDamage;


};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UE4GAME_API UProjectileShootingComponent : public UEventActorComponent
{
	GENERATED_BODY()

public:	
	UProjectileShootingComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FBullet Bullet;


protected:
	virtual void BeginPlay() override;
	void CreateDebugLocator(FVector Location);
	void CreateDebugLocator(FVector Location, AActor* AttachmentActor);
public:	
	UFUNCTION()
	void SpawnProjectile(FVector BulletSpreadDir, float Strength);
};
