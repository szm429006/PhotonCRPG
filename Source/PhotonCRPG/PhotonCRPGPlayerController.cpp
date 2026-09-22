// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhotonCRPGPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "PhotonCRPGCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Function/GlobalFunc.h"
#include "Public/Camera/CameraPawn.h"
#include "UI/Inventory/InventoryUI.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/UISystem.h"
#include "SubState/SubStateBase.h"
#include "Character/CharacterBase.h"
#include "UI/Character/CharacterUI.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

APhotonCRPGPlayerController::APhotonCRPGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void APhotonCRPGPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// 初始化、设置相机跟随角色
	CameraPawn = GetPawn<ACameraPawn>();
	if (IsValid(CameraPawn))
	{
		CameraPawn->Initialize();
		if (IsValid(CurCharacter))
		{
			CameraPawn->StartFollowingActor(CurCharacter);
		}
	}

	GameState = UGlobalFunc::GetGameState();
}

void APhotonCRPGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		UE_LOG(LogTemp, Warning, TEXT("AddMappingContext"));
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &APhotonCRPGPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &APhotonCRPGPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &APhotonCRPGPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &APhotonCRPGPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &APhotonCRPGPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &APhotonCRPGPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &APhotonCRPGPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &APhotonCRPGPlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(CamRotateAction, ETriggerEvent::Triggered, this, &APhotonCRPGPlayerController::OnCamRotate);
		EnhancedInputComponent->BindAction(CamMoveRightAction, ETriggerEvent::Triggered, this, &APhotonCRPGPlayerController::OnCamMoveRight);
		EnhancedInputComponent->BindAction(CamMoveForwardAction, ETriggerEvent::Triggered, this, &APhotonCRPGPlayerController::OnCamMoveForward);
		EnhancedInputComponent->BindAction(CamZoomAction, ETriggerEvent::Triggered, this, &APhotonCRPGPlayerController::OnCamZoom);
		EnhancedInputComponent->BindAction(CamResetAction, ETriggerEvent::Started, this, &APhotonCRPGPlayerController::OnCamReset);

		// 切换背包界面使用
		EnhancedInputComponent->BindAction(ToggleInventoryUIAction, ETriggerEvent::Started, this, &APhotonCRPGPlayerController::OnInventoryUIToggled);

		EnhancedInputComponent->BindAction(ToggleCharacterUIAction, ETriggerEvent::Started, this, &APhotonCRPGPlayerController::OnCharacterUIToggled);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APhotonCRPGPlayerController::OnInputStarted()
{
	// StopMovement();
	CurCharacter->GetController()->StopMovement();
	GameState->GetSubState()->MouseBeginClickAction();
}

// Triggered every frame when the input is held down
void APhotonCRPGPlayerController::OnSetDestinationTriggered()
{
	if (GameState->GetSubState()->IsTriggeringDetect())
	{
		// We flag that the input is being pressed
		FollowTime += GetWorld()->GetDeltaSeconds();

		// We look for the location in the world where the player has pressed the input
		FHitResult Hit;
		bool bHitSuccessful = false;
		if (bIsTouch)
		{
			bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
		}
		else
		{
			bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		}

		// If we hit a surface, cache the location
		if (bHitSuccessful)
		{
			CachedDestination = Hit.Location;
		}

		GameState->GetSubState()->MouseTriggeringAction();
	}
}

void APhotonCRPGPlayerController::OnSetDestinationReleased()
{
	GameState->GetSubState()->MouseEndClickAction();
}

// Triggered every frame when the input is held down
void APhotonCRPGPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void APhotonCRPGPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void APhotonCRPGPlayerController::OnInventoryUIToggled()
{
	UGlobalFunc::GetSubsystem<UUISystem>()->ToggleUI<UInventoryUI>();
	// UGlobalFunc::GetSubsystem<UUISystem>()->ToggleUI<UCharacterUI>();
}

void APhotonCRPGPlayerController::OnCharacterUIToggled()
{
	UGlobalFunc::GetSubsystem<UUISystem>()->ToggleUI<UCharacterUI>();
}

void APhotonCRPGPlayerController::OnCamRotate(const FInputActionInstance& Instance)
{
	CameraPawn->Rotate(Instance.GetValue().Get<float>());
}

void APhotonCRPGPlayerController::OnCamMoveRight(const FInputActionInstance& Instance)
{
	if (CameraPawn->bIsFollowingActor)
	{
		CameraPawn->StopFollowingActor();
	}
	CameraPawn->MoveRight(Instance.GetValue().Get<float>());
}

void APhotonCRPGPlayerController::OnCamMoveForward(const FInputActionInstance& Instance)
{
	if (CameraPawn->bIsFollowingActor)
	{
		CameraPawn->StopFollowingActor();
	}
	CameraPawn->MoveForward(Instance.GetValue().Get<float>());
}

void APhotonCRPGPlayerController::OnCamZoom(const FInputActionInstance& Instance)
{
	CameraPawn->Zoom(Instance.GetValue().Get<float>());
}

void APhotonCRPGPlayerController::OnCamReset()
{
	CameraPawn->ResetAll();
	if (IsValid(CurCharacter))
	{
		CameraPawn->StartFollowingActor(CurCharacter);
	}
}


void APhotonCRPGPlayerController::DoInputMove()
{
	// UE_LOG(LogTemp, Warning, TEXT("APhotonCRPGPlayerController::DoInputMove"));
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = CurCharacter;
	if (ControlledPawn != nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("APhotonCRPGPlayerController::DoInputMove ControllerPawn"));
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void APhotonCRPGPlayerController::DoSimpleMove()
{
	// UE_LOG(LogTemp, Warning, TEXT("APhotonCRPGPlayerController::DoSimpleMove"));
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// UE_LOG(LogTemp, Warning, TEXT("APhotonCRPGPlayerController::DoSimpleMove ShortPressThreshold"));
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(CurCharacter->GetController(), CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void APhotonCRPGPlayerController::SetCurCharacter(ACharacterBase* InCharacter)
{
	if (IsValid(InCharacter))
	{
		CurCharacter = InCharacter;
		if (IsValid(CameraPawn))
		{
			CameraPawn->StartFollowingActor(CurCharacter);
		}
	}
}
