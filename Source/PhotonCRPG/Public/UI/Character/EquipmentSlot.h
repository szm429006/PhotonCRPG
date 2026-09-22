// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/InventorySlot.h"
#include "EquipmentSlot.generated.h"

class FDragDropEvent;
struct FGeometry;
class UDragDropOperation;
class UImage;
class UEquipComponent;
enum class EItemType : uint8;
class UItemObject;
class UArmorObject;
class UWeaponObject;


/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UEquipmentSlot : public UInventorySlot
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Hint;

	UPROPERTY()
	TObjectPtr<UEquipComponent> EquipComp;

	bool bIsDragSameSlot;

	bool bIsDragSelf;

public:

	EItemType SlotType;

	uint8 SlotIndex;

protected:

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:

	void RefreshEquipInfo(UEquipComponent* InEquipComp);

	virtual void RefreshData(UItemObject* InItem, const int32 ShowNum = 1) override;

	FORCEINLINE void SetSlotInfo(const EItemType Type, const uint8 Index)
	{
		SlotType = Type;
		SlotIndex = Index;
	}

	virtual void DoAcquire() override;

	virtual void DoStore() override;

	virtual void DoDiscard() override;

protected:

	bool IsSameSlotItem(UItemObject* DragItem) const;
};
