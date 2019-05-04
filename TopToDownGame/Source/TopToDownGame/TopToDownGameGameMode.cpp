// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TopToDownGameGameMode.h"
#include "TopToDownGamePlayerController.h"
#include "TopToDownGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void ATopToDownGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	ATopToDownGameCharacter* MyCharacter = Cast<ATopToDownGameCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (PlayerHUDClass != nullptr) {

		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}

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