// Fill out your copyright notice in the Description page of Project Settings.


#include "EventActorComponent.h"

// Sets default values for this component's properties
UEventActorComponent::UEventActorComponent()
{
}


void UEventActorComponent::Initialize()
{
	EventManager = Cast<UEventManagerComponent>(GetOwner()->GetComponentByClass(UEventManagerComponent::StaticClass()));
	if (!EventManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Event Actor component is missing Event Manager!"));
	}
}

// Called when the game starts
void UEventActorComponent::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}
	
