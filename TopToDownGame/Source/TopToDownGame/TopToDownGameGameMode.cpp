// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TopToDownGameGameMode.h"
#include "TopToDownGamePlayerController.h"
#include "TopToDownGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopToDownGameGameMode::ATopToDownGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopToDownGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}