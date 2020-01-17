// Fill out your copyright notice in the Description page of Project Settings.


#include "AimingComponent.h"
#include "WeaponBase.h"
#include "UE4GameCharacter.h"
#include "Components/InputComponent.h"
// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AWeaponBase>(GetOwner());
	Owner->PickedUp.AddDynamic(this, &UAimingComponent::BindAim);
	// ...
	
}

void UAimingComponent::BindAim()
{
	Owner->OwningPlayer->InputComponent->BindAction("Aim", IE_Pressed, this, &UAimingComponent::Aim);
	Owner->OwningPlayer->InputComponent->BindAction("Aim", IE_Released, this, &UAimingComponent::UnAim);
}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

