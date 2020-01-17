// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4GameGameMode.h"
#include "UE4GameHUD.h"
#include "UE4GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4GameGameMode::AUE4GameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUE4GameHUD::StaticClass();
}
