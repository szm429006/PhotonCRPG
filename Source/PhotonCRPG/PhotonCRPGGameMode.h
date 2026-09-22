// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArticyFlowPlayer.h"
#include "PhotonCRPGGameMode.generated.h"

struct FArticyBranch;
class UArticyFlowPlayer;
struct FArticyRef;
class IArticyFlowObject;

UCLASS(minimalapi)
class APhotonCRPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APhotonCRPGGameMode();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArticyFlowPlayer> ArticyPlayer;

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UFUNCTION(BlueprintCallable)
	void ArticyPlayDialogueById(const int32 ArticyID) const;

	UFUNCTION(BlueprintCallable)
	void ArticyPlayDialogue(const FArticyRef Ref) const;

	UFUNCTION(BlueprintCallable)
	void ArticyEndDialogue() const;

protected:

	UFUNCTION()
	void OnArticyPlayerPaused(TScriptInterface<IArticyFlowObject> PausedOn);

	UFUNCTION()
	void OnArticyBranchesUpdated(const TArray<FArticyBranch>& AvailableBranches);
};



