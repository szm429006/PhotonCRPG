// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Character/EquipmentSlot.h"
#include "UI/Character/CharacterUI.h"
#include "Character/Components/EquipComponent.h"
#include "Item/ItemObject.h"
#include "Character/CharacterBase.h"
#include "Data/GlobalEnum.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/DragItem.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Item/ArmorObject.h"
#include "Item/WeaponObject.h"

void UEquipmentSlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

    const auto DragOperation = Cast<UItemDragDropOperation>(InOperation);
    if (IsValid(DragOperation))
    {
        bIsDragSameSlot = IsSameSlotItem(DragOperation->InventoryItem->GetItem());
        bIsDragSelf = Item == DragOperation->InventoryItem->GetItem();

        if (!bIsDragSelf)
        {
            Hint->SetVisibility(ESlateVisibility::Visible);
            Hint->SetBrushTintColor(bIsDragSameSlot ? FLinearColor::Green : FLinearColor::Red);
        }
    }
    else
    {
        bIsDragSameSlot = false;
        Hint->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UEquipmentSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDragLeave(InDragDropEvent, InOperation);

    bIsDragSameSlot = false;
    Hint->SetVisibility(ESlateVisibility::Collapsed);
}

bool UEquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Hint->SetVisibility(ESlateVisibility::Collapsed);
    const auto DragOperation = Cast<UItemDragDropOperation>(InOperation);
    if (IsValid(DragOperation))
    {
        if (bIsDragSameSlot && !bIsDragSelf)
        {
            UGlobalFunc::GetController()->GetCurCharacter()->GetEquipComp()->EquipToSlot(DragOperation->InventoryItem, this);
            UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadCastOnDragStatus(false);
            return true;
        }
    }

    return false;
}

void UEquipmentSlot::RefreshEquipInfo(UEquipComponent* InEquipComp)
{
    EquipComp = InEquipComp;

    switch (SlotType)
    {
    case EItemType::Armor:
        if (!EquipComp->GetArmors().IsEmpty())
        {
            const auto EquippedArmor = EquipComp->GetArmors().FindRef(static_cast<EArmorType>(SlotIndex));
            RefreshData(EquippedArmor, 1);
        }
        else
        {
            RefreshData(nullptr, 0);
        }
        break;
    case EItemType::Weapon:
        if (!EquipComp->GetWeapons().IsEmpty())
        {
            const auto EquippedWeapon = EquipComp->GetWeapons().FindRef(SlotIndex);
            RefreshData(EquippedWeapon, 1);
        }
        else
        {
            RefreshData(nullptr, 0);
        }
        break;
    default:
        break;
    }
}

void UEquipmentSlot::RefreshData(UItemObject* InItem, const int32 ShowNum)
{
    Super::RefreshData(InItem, ShowNum);
    Hint->SetVisibility(ESlateVisibility::Collapsed);
    NumText->SetVisibility(ESlateVisibility::Collapsed);
    NameText->SetVisibility(ESlateVisibility::Collapsed);
}

void UEquipmentSlot::DoAcquire()
{
    UGlobalFunc::GetSubsystem<UInventorySystem>()->AddItem(Item->GetItemID());
    EquipComp->UnEquipFromSlot(this);
}

void UEquipmentSlot::DoStore()
{
    UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadCastItemCollect(Item->GetItemID(), ItemNum);
    EquipComp->UnEquipFromSlot(this);
}

void UEquipmentSlot::DoDiscard()
{
    EquipComp->UnEquipFromSlot(this);
}

bool UEquipmentSlot::IsSameSlotItem(UItemObject* DragItem) const
{
    if (DragItem->GetItemData().ItemType != SlotType)
    {
        return false;
    }

    if (DragItem->GetItemData().ItemType == EItemType::Armor)
    {
        const auto DragArmor = Cast<UArmorObject>(DragItem);
        if (static_cast<EArmorType>(SlotIndex) != DragArmor->GetArmorType())
        {
            return false;
        }
    }
    return true;
}