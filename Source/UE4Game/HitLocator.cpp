// Fill out your copyright notice in the Description page of Project Settings.


#include "HitLocator.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AHitLocator::AHitLocator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	LocationMesh = CreateDefaultSubobject<UStaticMeshComponent>("Hit Mesh");
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Light Indicator");
	PointLight->AttachToComponent(LocationMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	PointLight->SetWorldLocation(LocationMesh->GetComponentLocation());
}

// Called when the game starts or when spawned
void AHitLocator::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(20);
}


