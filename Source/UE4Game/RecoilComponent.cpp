// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilComponent.h"
#include "WeaponBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "UE4GameCharacter.h"
// Sets default values for this component's properties
URecoilComponent::URecoilComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	



}


// Called when the game starts
void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();

	EventManager->OnWeaponShoot.AddDynamic(this, &URecoilComponent::RecoilFunction);
	EventManager->OnTriggerReleased.AddDynamic(this, &URecoilComponent::OnTriggerRelease);



	// ...
	
}


// Called every frame
void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



	// ...
}

void URecoilComponent::OnTriggerRelease()
{
	for (int i = 0; i < Counter; i++)
	{
		AWeaponBase* Owner = Cast<AWeaponBase>(GetOwner());
		OwnerController = Owner->OwningPlayer->GetController();
		float xRot = UKismetMathLibrary::RandomFloatInRange(-Strength, +Strength);
		OwnerController->SetControlRotation(FRotator(OwnerController->GetControlRotation() + FRotator(-Strength, 0, 0)));
	}
	Counter = 0;
}

void URecoilComponent::RecoilFunction()
{
	AWeaponBase* Owner = Cast<AWeaponBase>(GetOwner());
	OwnerController = Owner->OwningPlayer->GetController();
	float xRot = UKismetMathLibrary::RandomFloatInRange(-Strength, +Strength);
	OwnerController->SetControlRotation(FRotator(OwnerController->GetControlRotation() + FRotator(Strength, 0, 0)));
	Counter++;
}

