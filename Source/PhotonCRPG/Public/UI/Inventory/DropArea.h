// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropArea.generated.h"

class UUIBase;
class UInventorySlot;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDropArea : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TObjectPtr<UUIBase> ParentUI;

public:

	void HandleOnDrop(UInventorySlot* DropItem) const;

	FORCEINLINE void SetParent(UUIBase* InParentUI) { ParentUI = InParentUI; }
};
