// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UUIBase;
class UItemObject;
class UImage;
class UTextBlock;
class UDragItem;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDragItem> UDragItemClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NumText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY()
	TObjectPtr<UItemObject> Item;

	UPROPERTY()
	TObjectPtr<UUIBase> ParentUI;

	int32 ItemNum;

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void HandleOnDragCancelled(UDragDropOperation* Operation);

public:

	// 刷新
	virtual void RefreshData(UItemObject* InItem, const int32 ShowNum = 1);

	// 双击自动
	virtual void DoAutoAction();

	// 获得
	virtual void DoAcquire();

	// 储存
	virtual void DoStore();

	// 丢弃
	virtual void DoDiscard();

	// 设置图标的拖拽状态
	void SetIconDragStatus(const bool bIsDrag) const;

	FORCEINLINE UItemObject* GetItem() const { return Item; }

	FORCEINLINE void SetParent(UUIBase* InParentUI) { ParentUI = InParentUI; }

	FORCEINLINE UUIBase* GetParent() const { return ParentUI; }
};
