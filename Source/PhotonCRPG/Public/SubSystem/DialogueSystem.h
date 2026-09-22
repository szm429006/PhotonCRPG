// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ArticyFlowPlayer.h"
#include "DialogueSystem.generated.h"

struct FArticyBranch;
class UArticyFlowPlayer;
class IArticyFlowObject;

USTRUCT()
struct FDialogueInteractStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<int32> OptionIds;
};

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDialogueSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TMap<int32, FDialogueInteractStruct> InteractedOptions;

public:

	void ShowDialogueItem(UArticyFlowPlayer* ArticyPlayer, const TScriptInterface<IArticyFlowObject>& PausedOn);

	void UpdateOptionItem(UArticyFlowPlayer* ArticyPlayer, const TArray<FArticyBranch>& AvailableBranches);

	void SetOptionInteracted(const int32 ParentId, const int32 OptionId);

	bool IsOptionInteracted(const int32 ParentId, const int32 OptionId);
};
