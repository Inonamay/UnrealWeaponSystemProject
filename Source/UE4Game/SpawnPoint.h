// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacter.h"
#include "SpawnPoint.generated.h"

UCLASS()
class UE4GAME_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickRate = .1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemiesToSpawn = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AEnemyCharacter> EnemyClass;
	UFUNCTION()
	void RemoveEnemyFromList(AEnemyCharacter* enemytoremove);
protected:
	UPROPERTY()
		TArray<AEnemyCharacter*> Enemies;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void SpawnEnemy();
	FTimerHandle SpawnerTimerHandle;
public:	

};
