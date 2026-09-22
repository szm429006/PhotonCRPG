// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ContainerUI.h"
#include "SubSystem/InventorySystem.h"
#include "Item/ItemContainer.h"
#include "Item/ItemObject.h"
#include "UI/Inventory/ContainerSlot.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Function/GlobalFunc.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "UI/Inventory/DropArea.h"
#include "UI/Inventory/InventorySlot.h"
#include "UI/Inventory/ItemInfoPanel.h"
#include "Components/MenuAnchor.h"
#include "Item/ItemObject.h"
#include "UI/Inventory/ItemInfoPanel.h"

void UContainerUI::NativeOnInitialized()
{
    DropArea->SetParent(this);
    for (int32 i = 0; i < 10; i++)
    {
        AddSlot();
    }
    Super::NativeOnInitialized();
}

void UContainerUI::BindDelegates()
{
    CollectAllBtn->OnClicked.AddDynamic(this, &UContainerUI::CollectAll);
    CloseBtn->OnClicked.AddDynamic(this, &UContainerUI::DoCloseAction);
    UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemCollectDelegate.AddDynamic(this, &UContainerUI::CollectItem);
    HoverAnchor->OnGetUserMenuContentEvent.BindDynamic(this, &UContainerUI::GetInfoPanel);
}

void UContainerUI::UnbindDelegates()
{
    CollectAllBtn->OnClicked.Clear();
    CloseBtn->OnClicked.Clear();
    UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemCollectDelegate.RemoveDynamic(this, &UContainerUI::CollectItem);
    HoverAnchor->OnGetUserMenuContentEvent.Clear();
}

bool UContainerUI::NativeOnDrop(const FGeometry& InGeometryGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
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

void UContainerUI::ShowItems(AItemContainer* Container)
{
    ItemContainer = Container;
    const auto ContainedItems = Container->GetContainedItems();

    uint8 Index = 0;
    for (const auto Item : ContainedItems)
    {
        // 如果是可堆叠的物品，需要判断总数是否超出了堆叠数量，超出了要新增一格
        if (Item->GetItemData().bIsStackable)
        {
            // 首先需要计算出需要几格显示
            const bool bTotalDivided = Item->Num % Item->GetItemData().MaxStack == 0;
            //UE_LOG(LogTemp, Warning, TEXT("ItemNum: %d, MaxStack: %d, bTotalDivided: %d"), Item->Num, Item->GetItemData().MaxStack, bTotalDivided);

            const uint8 SlotNeed = Item->Num / Item->GetItemData().MaxStack + (bTotalDivided ? 0 : 1);
            //UE_LOG(LogTemp, Warning, TEXT("SlotNeed: %d"), SlotNeed);

            for (uint8 i = 0; i < SlotNeed; i++)
            {
                const uint8 ShowNum = (i < SlotNeed - 1 || bTotalDivided) ? Item->GetItemData().MaxStack : Item->Num % Item->GetItemData().MaxStack;
                //UE_LOG(LogTemp, Warning, TEXT("ShowNum: %d"), ShowNum);
                // 防越界处理，索引大于大于当前槽位数则生成新的槽位
                if (Index >= SlotItems.Num())
                {
                    AddSlot();
                }
                SlotItems[Index++]->RefreshData(Item, ShowNum);
            }
        }
        // 不可堆叠的物品，这每个物品只站一个槽位
        else
        {
            for (uint8 i = 0; i < Item->Num; i++)
            {
                if (Index >= SlotItems.Num())
                {
                    AddSlot();
                }
                SlotItems[Index++]->RefreshData(Item);
            }
        }
    }

    // 没用上的槽位，显示为空
    for(uint8 i = Index ; i< SlotItems.Num(); i++)
    {
        SlotItems[i]->RefreshData(nullptr);
    }

    CollectAllBtn->SetVisibility(Index > 0 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UContainerUI::DoUnload()
{
    Super::DoUnload();
    ItemContainer = nullptr;
}

void UContainerUI::DoCloseAction()
{
    Super::DoCloseAction();
}

void UContainerUI::CollectItem(const int32 ItemID, const int32 Num)
{
    if (IsValid(ItemContainer))
    {
        ItemContainer->AddItem(ItemID, -Num);
        ShowItems(ItemContainer);
    }
}

void UContainerUI::CollectAll()
{
    if (IsValid(ItemContainer))
    {
        ItemContainer->RemoveAll();
        ShowItems(ItemContainer);
    }
}

void UContainerUI::AddSlot()
{
    const auto ItemSlot = CreateWidget<UContainerSlot>(this, UContainerItemClass);
    InventoryPanel->AddChild(ItemSlot);
    ItemSlot->RefreshData(nullptr);
    ItemSlot->SetParent(this);
    SlotItems.Add(ItemSlot);
}

UUserWidget* UContainerUI::GetInfoPanel()
{
    if (IsValid(HoverItemSlot))
    {
        const auto MenuWidget = CreateWidget(this, HoverAnchor->MenuClass);
        const auto InfoPanel = Cast<UItemInfoPanel>(MenuWidget);
        InfoPanel->RefreshData(HoverItemSlot->GetItem());
        return MenuWidget;
    }
    return nullptr;
}

void UContainerUI::ShowInfoPanel(UInventorySlot* HoverItem)
{
    HoverItemSlot = HoverItem;
    HoverItemData = HoverItem->GetItem();
    IInventoryInterface::ShowInfoPanel(HoverItem);
    HoverAnchor->Open(false);
}

void UContainerUI::HideInfoPanel()
{
    HoverItemSlot = nullptr;
    HoverItemData = nullptr;
    IInventoryInterface::HideInfoPanel();
    HoverAnchor->Close();
}

void UContainerUI::StartHoverTick()
{
    IInventoryInterface::StartHoverTick();
    GetWorld()->GetTimerManager().SetTimer(HoverTimerHandle, this, &UContainerUI::OnHovering, 0.5f/60.0f, true);
}

void UContainerUI::OnHovering()
{
    IInventoryInterface::OnHovering();
    if (!IsValid(HoverItemSlot->GetItem()))
    {
        HideInfoPanel();
    }
    else if (HoverItemSlot->GetItem() != HoverItemData)
    {
        HoverItemData = HoverItemSlot->GetItem();
        HoverAnchor->Close();
        HoverAnchor->Open(false);
    }
}

void UContainerUI::EndHoverTick()
{
    IInventoryInterface::EndHoverTick();
    GetWorld()->GetTimerManager().ClearTimer(HoverTimerHandle);
}
