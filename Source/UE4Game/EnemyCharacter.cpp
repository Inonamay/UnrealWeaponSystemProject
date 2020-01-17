// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "SpawnPoint.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}




// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetLifeSpan() < .1f && GetLifeSpan() > 0) {
		OwningSpawnPoint->RemoveEnemyFromList(this);
	}
}

