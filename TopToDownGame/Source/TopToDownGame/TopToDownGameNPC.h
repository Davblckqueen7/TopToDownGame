// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "TopToDownGameNPC.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class TOPTODOWNGAME_API ATopToDownGameNPC : public ACharacter
{
	GENERATED_BODY()

public:
	ATopToDownGameNPC();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;


protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
	UPawnSensingComponent* PawnSensor;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
};
