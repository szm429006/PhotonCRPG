// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/DropArea.h"
#include "UI/Inventory/InventorySlot.h"
#include "UI/Inventory/ContainerSlot.h"
#include "UI/GameUI.h"
#include "UI/Inventory/InventoryUI.h"
#include "UI/Inventory/ContainerUI.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"

void UDropArea::HandleOnDrop(UInventorySlot* DropItem) const
{
    // 如果是在同一个界面中拖动，不处理
    if (ParentUI != DropItem->GetParent())
    {
        // 拖到背包界面
        if (ParentUI->IsA(UInventoryUI::StaticClass()))
        {
            DropItem->DoAcquire();
        }
        // 拖到容器界面
        else if (ParentUI->IsA(UContainerUI::StaticClass()))
        {
            DropItem->DoStore();
        }
        // 拖到主界面
        else if (ParentUI->IsA(UGameUI::StaticClass()))
        {
            DropItem->DoDiscard();
        }
    }
    else
    {
        DropItem->SetIconDragStatus(false);
    }

    UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadCastOnDragStatus(false);
}

