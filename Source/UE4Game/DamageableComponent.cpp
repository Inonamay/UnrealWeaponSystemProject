// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableComponent.h"
// Sets default values for this component's properties
UDamageableComponent::UDamageableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UDamageableComponent::Damage(int amount)
{
	HitPoints -= amount;
	if (HitPoints < 1) {
		GetOwner()->SetLifeSpan(0.01f);
	}
}

// Called when the game starts
void UDamageableComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


