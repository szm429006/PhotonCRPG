// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "ArticyFlowPlayer.h"
#include "DialogueUI.generated.h"

class UDialogueItem;
class UDialogueOption;
class UTextBlock;
class UScrollBox;
class UArticyFlowPlayer;
struct FArticyBranch;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDialogueUI : public UUIBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDialogueItem> UDialogueItemClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDialogueOption> UDialogueOptionClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SpeakerName;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> ContentScroll;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> OptionScroll;

public:

	virtual void DoLoad() override;

	virtual void DoUnload() override;

	virtual void DoClose(const float CloseTime = 5.f) override;

	void AddDialogueItem(const FText& Name, const FText& Content);

	UDialogueOption* AddOptionItem(UArticyFlowPlayer* ArticyPlayer, const FArticyBranch& Branch);

	// FORCEINLINE UScrollBox* GetContentScroll() const { return ContentScroll; }

	FORCEINLINE UScrollBox* GetOptionScroll() const { return OptionScroll; }
};
