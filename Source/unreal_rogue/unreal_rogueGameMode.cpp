// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "unreal_rogueGameMode.h"
#include "unreal_roguePlayerController.h"
#include "unreal_rogueCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aunreal_rogueGameMode::Aunreal_rogueGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = Aunreal_roguePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}