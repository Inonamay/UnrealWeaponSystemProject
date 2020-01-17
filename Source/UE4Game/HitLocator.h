// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitLocator.generated.h"

UCLASS()
class UE4GAME_API AHitLocator : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* LocationMesh;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UPointLightComponent* PointLight;
public:	
	// Sets default values for this actor's properties
	AHitLocator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
};
