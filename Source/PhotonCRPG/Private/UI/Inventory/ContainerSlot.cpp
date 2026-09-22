// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ContainerSlot.h"
#include "SubSystem/InventorySystem.h"
#include "Item/ItemContainer.h"
#include "Item/ItemObject.h"
#include "Function/GlobalFunc.h"

// 双击自动
void UContainerSlot::DoAutoAction()
{
    DoAcquire();
}

// 获得
void UContainerSlot::DoAcquire()
{
    UGlobalFunc::GetSubsystem<UInventorySystem>()->CollectItem(Item->GetItemID(), ItemNum);
}

// 储存
void UContainerSlot::DoStore()
{
}

// 丢弃
void UContainerSlot::DoDiscard()
{
    SetIconDragStatus(false);
}