// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryUI.h"
#include "Data/GlobalEnum.h"
#include "Data/ItemDataStruct.h"
#include "SubSystem/InventorySystem.h"
#include "Function/GlobalFunc.h"
#include "UI/Inventory/InventorySlot.h"
#include "Item/ItemObject.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI/Inventory/ItemTypeToggle.h"
#include "UI/Universal/UniversalToggle.h"
#include "UI/Inventory/DropArea.h"
#include "UI/Inventory/ItemDragDropOperation.h"
#include "Components/WrapBox.h"
#include "Character/Components/EquipComponent.h"
#include "UI/Inventory/ItemInfoPanel.h"
#include "Components/MenuAnchor.h"
#include "Item/ItemObject.h"

void UInventoryUI::NativeOnInitialized()
{
    DropArea->SetParent(this);
    for (const EItemType ItemType : TEnumRange<EItemType>())
    {
        const auto Toggle = CreateWidget<UItemTypeToggle>(this, UItemTypeToggleClass);
        Toggle->RefreshData(ItemType);
        Toggle->InitCallback([&] (const UUniversalToggle* SelToggle)
        { 
            OnToggleSelected(SelToggle);
        });

        ItemTypePanel->AddChild(Toggle);
        ItemTypeMap.Add(ItemType, Toggle);
    }

    // 设置页签
    ItemTypePanel->SetInnerSlotPadding(FVector2D(10.f, 5.f));

    //初始化默认添加20个格子
    for (uint8 i = 0; i < 20; i++)
    {
        AddSlot();
    }

    // 设置默认标签为全部
    CurType = EItemType::All;
    for (const auto Toggle : ItemTypeMap)
    {
        Toggle.Value->SetSelected(Toggle.Key == CurType);
    }

    Super::NativeOnInitialized();
}

void UInventoryUI::BindDelegates()
{
    CloseBtn->OnClicked.AddDynamic(this, &UInventoryUI::DoCloseAction);
    UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemChangeDelegate.AddDynamic(this, &UInventoryUI::OnRefreshInventory);
    HoverAnchor->OnGetUserMenuContentEvent.BindDynamic(this, &UInventoryUI::GetInfoPanel);
}

void UInventoryUI::UnbindDelegates()
{
    CloseBtn->OnClicked.Clear();
    UGlobalFunc::GetSubsystem<UInventorySystem>()->OnItemChangeDelegate.RemoveDynamic(this, &UInventoryUI::OnRefreshInventory);
    HoverAnchor->OnGetUserMenuContentEvent.Clear();
}

bool UInventoryUI::NativeOnDrop(const FGeometry& InGeometryGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
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

void UInventoryUI::DoLoad()
{
    Super::DoLoad();
    RefreshData();
}

void UInventoryUI::DoUnload()
{
    Super::DoUnload();
}

void UInventoryUI::RefreshData()
{
    uint8 Index = 0;
    for (UItemObject* Item : UGlobalFunc::GetSubsystem<UInventorySystem>()->GetItemsByType(CurType))
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
}

void UInventoryUI::OnRefreshInventory(const int32 ItemID)
{
    RefreshData();
}

void UInventoryUI::OnToggleSelected(const UUniversalToggle* SelToggle)
{
    const auto Toggle = Cast<UItemTypeToggle>(SelToggle);
    if (CurType == Toggle->GetItemType())
        return;

    ItemTypeMap[CurType]->SetSelected(false);
    CurType = Toggle->GetItemType();
    ItemTypeMap[CurType]->SetSelected(true);
    
    RefreshData();
}

void UInventoryUI::AddSlot()
{
    const auto ItemSlot = CreateWidget<UInventorySlot>(this, UInventorySlotClass);
    InventoryPanel->AddChild(ItemSlot);
    ItemSlot->RefreshData(nullptr);
    ItemSlot->SetParent(this);
    SlotItems.Add(ItemSlot);
}

UUserWidget* UInventoryUI::GetInfoPanel()
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

void UInventoryUI::ShowInfoPanel(UInventorySlot* HoverItem)
{
    HoverItemSlot = HoverItem;
    HoverItemData = HoverItem->GetItem();
    IInventoryInterface::ShowInfoPanel(HoverItem);
    HoverAnchor->Open(false);
}

void UInventoryUI::HideInfoPanel()
{
    HoverItemSlot = nullptr;
    HoverItemData = nullptr;
    IInventoryInterface::HideInfoPanel();
    HoverAnchor->Close();
}

void UInventoryUI::StartHoverTick()
{
    IInventoryInterface::StartHoverTick();
    GetWorld()->GetTimerManager().SetTimer(HoverTimerHandle, this, &UInventoryUI::OnHovering, 0.5f/60.0f, true);
}

void UInventoryUI::OnHovering()
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

void UInventoryUI::EndHoverTick()
{
    IInventoryInterface::EndHoverTick();
    GetWorld()->GetTimerManager().ClearTimer(HoverTimerHandle);
}

