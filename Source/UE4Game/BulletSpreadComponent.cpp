// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletSpreadComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"


UBulletSpreadComponent::UBulletSpreadComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBulletSpreadComponent::BeginPlay()
{
	Super::BeginPlay();
	EventManager->OnWeaponShoot.AddDynamic(this, &UBulletSpreadComponent::OnWeaponShoot);
	WeaponActor = Cast<AWeaponBase>(GetOwner());
}

void UBulletSpreadComponent::OnWeaponShoot()
{
	WeaponActor->SetBulletSpreadDirection(BulletSpreadFunction());
}

FVector UBulletSpreadComponent::BulletSpreadFunction_Implementation() 
{
	return UKismetMathLibrary::RandomUnitVectorInConeInDegrees(GetOwner()->GetActorRightVector(), BulletSpreadDegrees);
	
}





