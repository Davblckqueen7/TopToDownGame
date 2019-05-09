// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopToDownGameCharacter.generated.h"

UCLASS(Blueprintable)
class ATopToDownGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopToDownGameCharacter();

	/**Funcion de acceso a CurrentLife*/
	UFUNCTION(BlueprintPure, Category = "Life")
		float GetCurrentLife();

	/**Funcion de acceso a InitialLife*/
	UFUNCTION(BlueprintPure, Category = "Life")
		float GetInitialLife();

	/**Actuliza el valor de vida del coso*/
	UFUNCTION(BlueprintCallable, Category = "Life")
		void UpdateCurrentLife(float life);

	/**Funcion de acceso a LimitSeconds*/
	UFUNCTION(BlueprintPure, Category = "Life")
		int GetLimitSeconds();

	/**Funcion de acceso a LimitMinutes*/
	UFUNCTION(BlueprintPure, Category = "Life")
		int GetLimitMinutes();

	/**Funcion de acceso a TimeIsVisible*/
	UFUNCTION(BlueprintPure, Category = "Life")
		bool GetTimeIsVisible();


	/**Actuliza el tiempo*/
	UFUNCTION(BlueprintCallable, Category = "Life")
		void UpdateTime();

	UFUNCTION()
		void BeginPlay();
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:

	FTimerHandle TimerSeg;

	/**Character current life*/
	UPROPERTY(EditAnywhere, Category = "Life")
	float CurrentLife;

	UPROPERTY(EditAnywhere, Category = "Life")
		float InitialLife;

	/**Segundos de tiempo limite*/
	UPROPERTY(EditAnywhere, Category = "Life")
		int LimitSeconds;

	/**Segundos de tiempo limite*/
	UPROPERTY(EditAnywhere, Category = "Life")
		int LimitMinutes;

	/**True si el tiempo es visible en pantalla*/
	UPROPERTY(EditAnywhere, Category = "Life")
		bool TimeIsVisible;


	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

