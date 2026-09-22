// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UInventorySlot;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UInventorySlot> InventoryItem;
};
