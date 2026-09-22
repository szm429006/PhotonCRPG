// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventorySlot.h"
#include "UI/UIBase.h"
#include "Item/ItemObject.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/DragItem.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Character/Components/EquipComponent.h"
#include "Interfaces/InventoryInterface.h"

void UInventorySlot::RefreshData(UItemObject* InItem, const int32 ShowNum)
{
    Item = InItem;
    ItemNum = ShowNum;
    if (IsValid(Item))
    {
        // const auto IconResource = LoadObject<UTexture2D>(nullptr, *InItem->GetInfoData().Icon);
        const auto IconResource = UGlobalFunc::GetCachedIcon(InItem->GetInfoData().Icon);
        if (IconResource != nullptr)
        {
            Icon->SetBrushFromTexture(IconResource);
            Icon->SetVisibility(ESlateVisibility::Visible);
        }

        if (ItemNum > 1)
        {
            NumText->SetText(FText::AsNumber(ItemNum));
            NumText->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            NumText->SetVisibility(ESlateVisibility::Collapsed);
        }

        if (InItem->GetInfoData().Name.Len() > 4)
        {
            FText LimitedText = FText::FromString(InItem->GetInfoData().Name.Left(4) + TEXT("..."));
            NameText->SetText(LimitedText);
        }
        else
        {
            NameText->SetText(FText::FromString(InItem->GetInfoData().Name));
        }
        
        NameText->SetVisibility(ESlateVisibility::Visible);

        SetIconDragStatus(false);
    }
    else
    {
        Icon->SetVisibility(ESlateVisibility::Collapsed);
        NumText->SetVisibility(ESlateVisibility::Collapsed);
        NameText->SetVisibility(ESlateVisibility::Collapsed);
    }
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
    // 当鼠标左键按下时，检测拖拽
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        if (IsValid(Item))
        {
            return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
        }
    }
    // 当鼠标右键按下时，可弹出选项菜单（未实现）
    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        return Reply.Handled();
    }
    return Reply.Unhandled();
}

FReply UInventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
    // 当鼠标左键双击时，自动使用该物品
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        if (IsValid(Item))
        {
            DoAutoAction();
            return Reply.Handled();
        }
    }
    return Reply.Unhandled();
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    const auto DragItem = CreateWidget<UDragItem>(this, UDragItemClass);

    DragItem->SetContent(Item);

    const auto DragOperation = NewObject<UItemDragDropOperation>(this);
    DragOperation->InventoryItem = this;
    DragOperation->DefaultDragVisual = DragItem;
    DragOperation->Pivot = EDragPivot::TopLeft;
    DragOperation->OnDragCancelled.AddDynamic(this, &UInventorySlot::HandleOnDragCancelled);

    OutOperation = DragOperation;
    SetIconDragStatus(true);

    UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadCastOnDragStatus(true);
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
    if (!IsValid(Item))
    {
        return;
    }

    Cast<IInventoryInterface>(ParentUI)->ShowInfoPanel(this);
}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
    if (!IsValid(Item))
    {
        return;
    }

    Cast<IInventoryInterface>(ParentUI)->HideInfoPanel();
}

void UInventorySlot::HandleOnDragCancelled(UDragDropOperation* Operation)
{
    Operation->OnDragCancelled.Clear();
    SetIconDragStatus(false);
    UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadCastOnDragStatus(false);
}

// 双击自动
void UInventorySlot::DoAutoAction()
{
    // 双击时候自动装备
    UGlobalFunc::GetController()->GetCurCharacter()->GetEquipComp()->AutoEquip(Item);
}

// 获得
void UInventorySlot::DoAcquire()
{}

// 储存
void UInventorySlot::DoStore()
{
    // 把一个物品从背包拖回容器
    UGlobalFunc::GetSubsystem<UInventorySystem>()->CollectItem(Item->GetItemID(), -ItemNum);
}

// 丢弃
void UInventorySlot::DoDiscard()
{
    UGlobalFunc::GetSubsystem<UInventorySystem>()->ReduceItem(Item->GetItemID(), ItemNum);
}

// 设置图标的拖拽状态
void UInventorySlot::SetIconDragStatus(const bool bIsDrag) const
{
    if (bIsDrag)
    {
        Icon->SetBrushTintColor(FLinearColor::Gray);
    }
    else
    {
        Icon->SetBrushTintColor(FLinearColor::White);
    }
}
