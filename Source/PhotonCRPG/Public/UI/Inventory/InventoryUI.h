// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropArea.h"
#include "ItemTypeToggle.h"
#include "UI/UIBase.h"
#include "Interfaces/InventoryInterface.h"
#include "InventoryUI.generated.h"

class UButton;
class UWrapBox;
class UInventorySlot;
enum class EItemType : uint8;
class UUniversalToggle;
class UItemTypeToggle;
class UDropArea;
class UDragDropOperation;
class UItemInfoPanel;
class UItemObject;
class UMenuAnchor;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UInventoryUI : public UUIBase, public IInventoryInterface
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UItemTypeToggle> UItemTypeToggleClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlot> UInventorySlotClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> ItemTypePanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> InventoryPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UDropArea> DropArea;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CloseBtn;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMenuAnchor> HoverAnchor;

	UPROPERTY()
	TMap<EItemType, TObjectPtr<UItemTypeToggle>> ItemTypeMap;

	UPROPERTY(meta=(BindWidget))
	TArray<TObjectPtr<UInventorySlot>> SlotItems;

	EItemType CurType;

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

	virtual void DoLoad() override;

	virtual void DoUnload() override;

	void RefreshData();

protected:

	void OnToggleSelected(const UUniversalToggle* SelToggle);

	UFUNCTION()
	void OnRefreshInventory(const int32 ItemID);

private:

	void AddSlot();

	virtual UUserWidget* GetInfoPanel();

	virtual void ShowInfoPanel(UInventorySlot* HoverItem);

	virtual void HideInfoPanel();

	virtual void StartHoverTick();

	virtual void OnHovering();

	virtual void EndHoverTick();
};
