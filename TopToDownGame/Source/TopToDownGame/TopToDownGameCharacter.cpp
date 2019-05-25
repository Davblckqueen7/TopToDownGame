// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TopToDownGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Engine/Engine.h"
#include "MySaveGame.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ATopToDownGameCharacter::ATopToDownGameCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	InitialLife = 1.0f;
	CurrentLife = InitialLife;
	LimitSeconds = 0;
	LimitMinutes = 1;
	TimeIsVisible = true;
	JumpIsPossible = true;
}

float ATopToDownGameCharacter::GetCurrentLife()
{
	return CurrentLife;
}

float ATopToDownGameCharacter::GetInitialLife()
{
	return InitialLife;
}

void ATopToDownGameCharacter::SaveGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->PlayerPosition = this->GetActorLocation();
	SaveGameInstance->PlayerLife = this->GetCurrentLife();
	SaveGameInstance->Minutes = this->GetLimitMinutes();
	SaveGameInstance->Seconds = this->GetLimitSeconds();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Slot1"), 0);

}

void ATopToDownGameCharacter::LoadGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"),0));
	this->SetActorLocation(SaveGameInstance->PlayerPosition);
	this->SetLife(SaveGameInstance->PlayerLife);
	this->SetMinutes(SaveGameInstance->Minutes);
	this->SetSeconds(SaveGameInstance->Seconds);
}

void ATopToDownGameCharacter::UpdateCurrentLife(float life)
{
	CurrentLife += life;
}

void ATopToDownGameCharacter::RedLife()
{
	CurrentLife -= 0.25f;
}

void ATopToDownGameCharacter::SetLife(float life)
{
	CurrentLife = life;
}

int ATopToDownGameCharacter::GetLimitSeconds()
{
	return LimitSeconds;
}

int ATopToDownGameCharacter::GetLimitMinutes()
{
	return LimitMinutes;
}

void ATopToDownGameCharacter::SetMinutes(float Min)
{
	LimitMinutes = Min;
}

void ATopToDownGameCharacter::SetSeconds(float Sec)
{
	LimitSeconds = Sec;
}

bool ATopToDownGameCharacter::GetTimeIsVisible()
{
	return TimeIsVisible;
}

bool ATopToDownGameCharacter::GetJumpIsPossible()
{
	return JumpIsPossible;
}

void ATopToDownGameCharacter::UpdateTime()
{
	if (LimitSeconds > 0) {
		LimitSeconds -= 1;
	}
	else {
		if (LimitMinutes > 0) {
			LimitMinutes -= 1;
			LimitSeconds = 59;
		}
		
	}
}


void ATopToDownGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerSeg, this, &ATopToDownGameCharacter::UpdateTime, 1.0f, true);
}

void ATopToDownGameCharacter::Tick(float DeltaSeconds)
{


    Super::Tick(DeltaSeconds);

	//UpdateCurrentLife(-DeltaSeconds * 0.01f*InitialLife);

	InputComponent->BindAction("ReduccionVida", IE_Pressed, this, &ATopToDownGameCharacter::RedLife);
	
	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}
