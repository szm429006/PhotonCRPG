// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueItem.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDialogueItem : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextContent;

public:

	void RefreshData(const FText& Content) const;

	void SetIsRead();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnReadBP();
};
