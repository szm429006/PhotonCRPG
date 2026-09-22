// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/InventorySlot.h"
#include "ContainerSlot.generated.h"

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UContainerSlot : public UInventorySlot
{
	GENERATED_BODY()

public:

	// 双击自动
	virtual void DoAutoAction() override;

	// 获得
	virtual void DoAcquire() override;

	// 储存
	virtual void DoStore() override;

	// 丢弃
	virtual void DoDiscard() override;
};
