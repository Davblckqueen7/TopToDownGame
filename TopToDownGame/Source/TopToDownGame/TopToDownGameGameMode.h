// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TopToDownGameGameMode.generated.h"

UCLASS(minimalapi)
class ATopToDownGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
		virtual void BeginPlay() override;


public:
	ATopToDownGameGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget>PlayerHUDClass;

	UPROPERTY()
		class UUserWidget* CurrentWidget;
};



