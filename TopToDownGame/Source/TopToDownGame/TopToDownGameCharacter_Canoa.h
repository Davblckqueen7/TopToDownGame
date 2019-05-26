// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopToDownGameCharacter_Canoa.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOPTODOWNGAME_API ATopToDownGameCharacter_Canoa : public ACharacter
{
	GENERATED_BODY()

public:
	ATopToDownGameCharacter_Canoa();

	/**Funcion de acceso a CurrentLife*/
	UFUNCTION(BlueprintPure, Category = "Life")
		float GetCurrentLife();

	/**Funcion de acceso a InitialLife*/
	UFUNCTION(BlueprintPure, Category = "Life")
		float GetInitialLife();

	/**guardado*/
	UFUNCTION(BlueprintCallable)
		void SaveGame();

	/**Cargar*/
	UFUNCTION(BlueprintCallable)
		void LoadGame();


	/**Actuliza el valor de vida del coso*/
	UFUNCTION(BlueprintCallable, Category = "Life")
		void UpdateCurrentLife(float life);

	/**Actuliza el valor de vida del coso*/
	UFUNCTION(BlueprintCallable, Category = "Life")
		void RedLife();

	/**Setlife*/
	UFUNCTION(BlueprintCallable, Category = "Life")
		void SetLife(float life);

	/**Funcion de acceso a LimitSeconds*/
	UFUNCTION(BlueprintPure, Category = "Life")
		int GetLimitSeconds();

	/**Funcion de acceso a LimitMinutes*/
	UFUNCTION(BlueprintPure, Category = "Life")
		int GetLimitMinutes();

	UFUNCTION()
		void SetMinutes(float Min);

	UFUNCTION()
		void SetSeconds(float Sec);

	/**Funcion de acceso a TimeIsVisible*/
	UFUNCTION(BlueprintPure, Category = "Life")
		bool GetTimeIsVisible();

	UFUNCTION(BlueprintPure, Category = "Life")
		bool GetJumpIsPossible();

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

	UPROPERTY(EditAnywhere, Category = "Life")
		bool JumpIsPossible;


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
