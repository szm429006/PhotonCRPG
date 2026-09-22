// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

class UInventorySlot;
class UUserWidget;


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PHOTONCRPG_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual UUserWidget* GetInfoPanel();

	virtual void ShowInfoPanel(UInventorySlot* HoverItem);

	virtual void HideInfoPanel();

	virtual void StartHoverTick();

	UFUNCTION()
	virtual void OnHovering();

	virtual void EndHoverTick();
};
