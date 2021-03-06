// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TOPTODOWNGAME_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMySaveGame();

	UPROPERTY()
		FVector PlayerPosition;
	UPROPERTY()
	float PlayerLife; 
	UPROPERTY()
		int Minutes;
	UPROPERTY()
		int Seconds;
	
};
