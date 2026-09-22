// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI.h"
#include "Components/Button.h"
#include "SubSystem/UISystem.h"
#include "UI/Inventory/InventoryUI.h"
#include "Function/GlobalFunc.h"
#include "UI/Inventory/DropArea.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Data/GlobalEnum.h"

void UGameUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DropArea->SetParent(this);
	DropArea->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	StartBtn->SetVisibility(ESlateVisibility::Collapsed);
}

void UGameUI::BindDelegates()
{
	InventoryBtn->OnClicked.AddDynamic(this, &UGameUI::ToggleInventoryUI);
	StartBtn->OnClicked.AddDynamic(this, &UGameUI::BattleStart);
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnDragStatusDelegate.AddUObject(this, &UGameUI::OnItemDrag);
}

void UGameUI::UnbindDelegates()
{
	InventoryBtn->OnClicked.Clear();
	UGlobalFunc::GetSubsystem<UInventorySystem>()->OnDragStatusDelegate.Clear();
}

bool UGameUI::NativeOnDrop(const FGeometry& InGeometryGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    const auto DragDropOperation = Cast<UItemDragDropOperation>(InOperation);
    if (IsValid(DragDropOperation))
    {
        // 判断物品放下是否处于放置区域的屏幕坐标中
        if (DropArea->GetCachedGeometry().IsUnderLocation(InDragDropEvent.GetScreenSpacePosition()))
        {
            DropArea->HandleOnDrop(DragDropOperation->InventoryItem);
            return true;
        }
    }
    return false;
}

void UGameUI::OnItemDrag(const bool bIsDragging)
{
	// 当检查到物品拖拽时，设置DropArea可视状态（没有拖拽时不要阻拦对场景中的UI点击）
	if (bIsDragging)
	{
		DropArea->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		DropArea->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UGameUI::ToggleInventoryUI()
{
	//UGlobalFunc::GetSubsystem<UUISystem>()->ToggleUI<UInventoryUI>();
	//GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UUISystem>()->ToggleUI<UInventoryUI>();
}

void UGameUI::BattleStart()
{
	UGlobalFunc::SetGameStateType(EGameStateType::Normal);
}

void UGameUI::ShowStartBtn(const bool bIsShow)
{
	if (bIsShow)
	{
		StartBtn->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		StartBtn->SetVisibility(ESlateVisibility::Collapsed);
	}
}
