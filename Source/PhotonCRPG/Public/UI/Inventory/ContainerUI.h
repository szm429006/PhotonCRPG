// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "Interfaces/InventoryInterface.h"
#include "ContainerUI.generated.h"

class AItemContainer;
class UContainerSlot;
class UButton;
class UWrapBox;
class UDropArea;
class UDragDropOperation;
class UUserWidget;
class UInventorySlot;
class UMenuAnchor;
class UItemObject;
class IInventoryInterface;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UContainerUI : public UUIBase, public IInventoryInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UContainerSlot> UContainerItemClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> InventoryPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UDropArea> DropArea;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CollectAllBtn;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CloseBtn;

	UPROPERTY()
	TObjectPtr<AItemContainer> ItemContainer;

	UPROPERTY()
	TArray<TObjectPtr<UContainerSlot>> SlotItems;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMenuAnchor> HoverAnchor;

protected:

	UPROPERTY()
	TObjectPtr<UInventorySlot> HoverItemSlot;

	UPROPERTY()
	TObjectPtr<UItemObject> HoverItemData;

	FTimerHandle HoverTimerHandle;

protected:

	virtual void NativeOnInitialized() override;

	virtual void BindDelegates() override;

	virtual void UnbindDelegates() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometryGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:

	UFUNCTION(BlueprintCallable)
	void ShowItems(AItemContainer* Container);

	virtual void DoUnload() override;

	virtual void DoCloseAction() override;

protected:

	UFUNCTION()
	void CollectItem(const int32 ItemID, const int32 Num);

	UFUNCTION()
	void CollectAll();

private:

	void AddSlot();

	virtual UUserWidget* GetInfoPanel();

	virtual void ShowInfoPanel(UInventorySlot* HoverItem);

	virtual void HideInfoPanel();

	virtual void StartHoverTick();

	virtual void OnHovering();

	virtual void EndHoverTick();
};
