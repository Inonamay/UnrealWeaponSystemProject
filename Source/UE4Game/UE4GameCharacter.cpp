// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4GameCharacter.h"
#include "UE4GameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "WeaponBase.h"
#include "Interactable_Interface.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);
AUE4GameCharacter::AUE4GameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}

void AUE4GameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AUE4GameCharacter::Interact()
{
	FHitResult Hit;
	float RayLength = 500;
	FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndLocation = StartLocation + (FirstPersonCameraComponent->GetForwardVector() * RayLength);
	FCollisionQueryParams CollisionParameters(FName(TEXT("TraceGround")), false, this);
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic, CollisionParameters);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 2, 5, 1.f);
	if (Hit.Actor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("I Hit: %s"), *Hit.Actor->GetName()));
		IInteractable_Interface* HitInteractable = Cast<IInteractable_Interface>(Hit.Actor);
		if (HitInteractable) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Pickupable!")));
			Cast<IInteractable_Interface>(Hit.Actor)->Interact_Implementation(this);
		}
	}
}
void AUE4GameCharacter::EquipWeapon(AWeaponBase* weapon)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->SetActorHiddenInGame(true);
	}
	weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "GripPoint");
	if (Mesh1P->bHiddenInGame)
	{
		Mesh1P->SetHiddenInGame(false, false);
	}
	EquippedWeapon = weapon;
	Weapons.Add(EquippedWeapon);
}
void AUE4GameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	InputComponent = PlayerInputComponent;
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUE4GameCharacter::OnFirePress);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AUE4GameCharacter::OnFireRelease);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AUE4GameCharacter::Interact);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AUE4GameCharacter::Reload);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUE4GameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUE4GameCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AUE4GameCharacter::OnFirePress()
{
	if (EquippedWeapon) { EquippedWeapon->OnFire(); }
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	if (FireAnimation)
	{
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AUE4GameCharacter::OnFireRelease()
{
	if(EquippedWeapon) {
		EquippedWeapon->OnStopFire();
	}
}



void AUE4GameCharacter::Reload()
{
	if (EquippedWeapon && EquippedWeapon->FindComponentByClass<UAmmoComponent>())
	{
		UAmmoComponent* WeaponAmmo = EquippedWeapon->FindComponentByClass<UAmmoComponent>();
		WeaponAmmo->Reload(1, WeaponAmmo->GetCurrentAmmoIndex());
	}
}

void AUE4GameCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AUE4GameCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}