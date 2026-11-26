// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArticyFlowPlayer.h"
#include "DialogueOption.generated.h"

class UArticyFlowPlayer;
class UArticyObject;
struct FArticyBranch;
class UButton;
class UTextBlock;
class UPhotoncrpggDiaRollTemplate;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDialogueOption : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TextContent;
		
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> DiceContent;

	UPROPERTY()
	TObjectPtr<UArticyFlowPlayer> DialoguePlayer;

	UPROPERTY()
	TObjectPtr<UPhotoncrpggDiaRollTemplate> RollTemplate;

	FArticyBranch DialogueBranch;

public:

	int32 SortOrder;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInteracted;

private:

	int32 ParentId;

	int32 OptionId;

	bool bIsContinue;

	bool bIsClose;

protected:

	virtual void NativeConstruct() override;

public:

	void RefreshData(UArticyFlowPlayer* ArticyPlayer, const FArticyBranch& Branch);

protected:

	UFUNCTION()
	void OnClickAction();
};
