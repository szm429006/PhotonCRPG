// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ContainerUI.h"
#include "UI/UIBase.h"
#include "GameUI.generated.h"

class UButton;
class UDropArea;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UGameUI : public UUIBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> InventoryBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartBtn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDropArea> DropArea;

protected:

	// 初始化
	virtual void NativeOnInitialized() override;

	// 绑定委托
	virtual void BindDelegates() override;

	// 解绑委托
	virtual void UnbindDelegates() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION()
	void OnItemDrag(const bool bIsDragging);

protected:

	UFUNCTION()
	void ToggleInventoryUI();

	UFUNCTION()
	void BattleStart();

public:

	void ShowStartBtn(const bool bIsShow);
};
