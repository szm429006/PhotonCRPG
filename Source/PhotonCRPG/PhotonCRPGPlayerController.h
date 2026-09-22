// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PhotonCRPGCharacter.h"
#include "Public/Camera/CameraPawn.h"
#include "Public/PhotonCRPGGameState.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraPawn.h"
#include "EnhancedInput/Public/InputAction.h"
#include "PhotonCRPGPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class ACharacterBase;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class APhotonCRPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APhotonCRPGPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	// 切换背包界面使用
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ToggleInventoryUIAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ToggleCharacterUIAction;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CamRotateAction;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CamMoveRightAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CamMoveForwardAction;

	// 切换背包界面使用
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CamZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CamResetAction;

	UPROPERTY()
	TObjectPtr<ACharacterBase> CurCharacter;

	UPROPERTY()
	TObjectPtr<ACameraPawn> CameraPawn;

	UPROPERTY()
	TObjectPtr<APhotonCRPGGameState> GameState;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

	void OnInventoryUIToggled();
	void OnCharacterUIToggled();
	// void OnToggleInventoryReleased();
	// void OnToggleInventoryClicked();

	void OnCamRotate(const FInputActionInstance& Instance);
	void OnCamMoveRight(const FInputActionInstance& Instance);
	void OnCamMoveForward(const FInputActionInstance& Instance);
	void OnCamZoom(const FInputActionInstance& Instance);
	void OnCamReset();

public:

	UFUNCTION(BlueprintCallable)
	void SetCurCharacter(ACharacterBase* InCharacter);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ACharacterBase* GetCurCharacter() { return CurCharacter; }

	void DoInputMove();

	void DoSimpleMove();

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


