// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/InventorySystem.h"
#include "Data/ItemDataStruct.h"
#include "Data/GlobalEnum.h"
#include "Item/ItemObject.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/DataSystem.h"
#include "Item/ItemObject.h"
#include "Item/ArmorObject.h"
#include "Item/WeaponObject.h"

void UInventorySystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/ItemDataTable"));
}

TArray<UItemObject*> UInventorySystem::GetAllItems()
{
	TArray<UItemObject*> AllItems;
	for (const TTuple<EItemType, FTypeItemHolder> TypeItem : Inventory)
	{
		for (const TObjectPtr<UItemObject> Item : TypeItem.Value.ItemArray)
		{
			AllItems.Add(Item);
		}
	}
	return AllItems;
}

TArray<UItemObject*> UInventorySystem::GetItemsByType(const EItemType ItemType)
{
    if (ItemType == EItemType::All)
    {
        return GetAllItems();
    }
    return Inventory.FindRef(ItemType).ItemArray;
}

UItemObject* UInventorySystem::AddItem(const int32 ItemID, const int32 Num, const bool bAutoBroadCast)
{
	// const auto ItemData = GetItemData(ItemID);

    //UE_LOG(LogTemp, Warning, TEXT("获取ItemData: %s"), *ItemData->Name);

	// if (!ItemData)
	// {
	// 	return nullptr;
	// }

	const EItemType ItemType = GetItemType(ItemID);

    if (ItemType == EItemType::All)
    {
        return nullptr;
    }

	//先找出同类物品的队列，没有就创建一个
	if (!Inventory.Contains(ItemType))
	{
        //UE_LOG(LogTemp, Warning, TEXT("此物品信息: %d"), ItemType);
		const FTypeItemHolder TypeItems;
		Inventory.Add(ItemType, TypeItems);
        //UE_LOG(LogTemp, Warning, TEXT("此物品个数信息: %d"), TypeItems.ItemArray.Num());
	}

	FTypeItemHolder CurTypeItems = Inventory.FindRef(ItemType);
    const TObjectPtr<UItemObject>* CurItem = nullptr;
    if (CurTypeItems.ItemArray.Num() > 0)
    {
        //UE_LOG(LogTemp, Warning, TEXT("数组内包含物品信息：%d个"), CurTypeItems.ItemArray.Num());
        CurItem = CurTypeItems.ItemArray.FindByPredicate([ItemID](const UItemObject* ArrayItem)
        {
            return ArrayItem->GetItemID() == ItemID;
        });
    }

    // const TObjectPtr<UItemObject>* CurItem = CurTypeItems.ItemArray.FindByPredicate([ItemID](const UItemObject* ArrayItem)
    //     {
    //         return ArrayItem->GetItemID() == ItemID;
    //     });

	// 在队列中查找现有道具，有的话进行数量计算
	if (CurItem)
	{
		const TObjectPtr<UItemObject> CurItemRef = *CurItem;
		CurItemRef->Num += Num;
        //UE_LOG(LogTemp, Warning, TEXT("队列中物品: %s, 变更数量: %d"), *CurItemRef->GetItemData().Name, Num);
        //UE_LOG(LogTemp, Warning, TEXT("队列中已有此物品: %s, 数量: %d"), *CurItemRef->GetItemData().Name, CurItemRef->Num);

		// 如果数量小于0，删除
		if (CurItemRef->Num <= 0) 
		{
            //UE_LOG(LogTemp, Warning, TEXT("此物品: %s, 数量小于0，进行移除"), *CurItemRef->GetItemData().Name);
			CurTypeItems.ItemArray.Remove(CurItemRef);
			Inventory.Add(ItemType, CurTypeItems);
		}

		if (bAutoBroadCast)
		{
            if (OnItemChangeDelegate.IsBound())
            {
                OnItemChangeDelegate.Broadcast(ItemID);
            }
		}

		return CurItemRef;
	}

	// // 没有的话进行数量计算
	if (Num > 0)
	{
		const TObjectPtr<UItemObject> NewItem = CreateItem(ItemID);
        if (!IsValid(NewItem))
        {
            //UE_LOG(LogTemp, Warning, TEXT("创建物品失败"));
            return nullptr;
        }
		NewItem->Num = Num;

        //UE_LOG(LogTemp, Warning, TEXT("队列中没有此物品: %s,新建, 数量为: %d"), *NewItem->GetItemData().Name, NewItem->Num);

		CurTypeItems.ItemArray.Add(NewItem);
		Inventory.Add(ItemType, CurTypeItems);


		if (bAutoBroadCast)
		{
            if (OnItemChangeDelegate.IsBound())
            {
                OnItemChangeDelegate.Broadcast(ItemID);
            }
		}

		return NewItem;
	}
	return nullptr;
}

UItemObject* UInventorySystem::ReduceItem(const int32 ItemID, const int32 Num, const bool bAutoBroadCast)
{
    return AddItem(ItemID, -Num, bAutoBroadCast);
}

void UInventorySystem::CollectItem(const int32 ItemID, const int32 Num)
{
    AddItem(ItemID, Num, true);
    if (OnItemCollectDelegate.IsBound())
    {
        OnItemCollectDelegate.Broadcast(ItemID, Num);
    }
}

EItemType UInventorySystem::GetItemType(const int32 ItemID) const
{
    const auto TbItemData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbItemData(ItemID);
	if (TbItemData != nullptr)
	{
		return static_cast<EItemType>(TbItemData->itemData->type);
	}
	return EItemType::All;
}



// FItemData* UInventorySystem::GetItemData(const int32 ItemID) const
// {
// 	if (IsValid(ItemDataTable))
// 	{
// 		FItemData* ItemData = ItemDataTable->FindRow<FItemData>(FName(FString::FromInt(ItemID)), TEXT(""));
// 		return ItemData;
// 	}
// 	return nullptr;
// }

UItemObject* UInventorySystem::GetItem(const int32 ItemID) const
{
	// const auto ItemData = GetItemData(ItemID);
	// if (!ItemData)
	// 	return nullptr;

	const EItemType ItemType = GetItemType(ItemID);

    if (ItemType == EItemType::All)
    {
        return nullptr;
    }

	if (!Inventory.Contains(ItemType))
		return nullptr;

	auto CurTypeItems = Inventory.FindRef(ItemType);
	const auto CurItem = CurTypeItems.ItemArray.FindByPredicate([ItemID](const UItemObject* ArrayItem)
		{
			return ArrayItem->GetItemID() == ItemID;
		});

    if (CurItem)
    {
        return *CurItem;
    }
    return nullptr;
}

int32 UInventorySystem::GetItemNum(const int32 ItemID) const
{
    const auto CurItem = GetItem(ItemID);
    if (!IsValid(CurItem))
    {
        return 0;
    }
	return CurItem->Num;
}

UItemObject* UInventorySystem::CreateItem(const int32 ItemID) const
{
    // const auto ItemData = GetItemData(ItemID);
    // if (!ItemData)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("获取ItemData失败"));
    //     return nullptr;
    // }

    const EItemType ItemType = GetItemType(ItemID);

    if (ItemType == EItemType::All)
    {
        return nullptr;
    }

    // const EItemType ItemType = ItemData->ItemType;
    // UE_LOG(LogTemp, Warning, TEXT("物品类型: %d"), ItemType);
    if (ItemType == EItemType::All)
    {
        return nullptr;
    }

    UItemObject* Item;
    switch (ItemType)
    {
        case EItemType::Armor:
            Item = NewObject<UArmorObject>();
            break;
        case EItemType::Weapon:
            Item = NewObject<UWeaponObject>();
            break;
        case EItemType::Collectable:
        case EItemType::Consumable:
        case EItemType::Prop:
        case EItemType::Quest:
        case EItemType::Mundane:
        default:
            Item = NewObject<UItemObject>();
            break;
    }

    Item->Initialize(ItemID);
	return Item;
}

void UInventorySystem::BroadCastItemChange() const
{
    if (OnItemChangeDelegate.IsBound())
    {
        OnItemChangeDelegate.Broadcast(0);
    }
}

void UInventorySystem::BroadCastItemCollect(const int32 ItemID, const int32 Num) const
{
    if (OnItemCollectDelegate.IsBound())
    {
        OnItemCollectDelegate.Broadcast(ItemID, Num);
    }
}

void UInventorySystem::BroadCastOnDragStatus(const bool bIsDragging) const
{
    if (OnDragStatusDelegate.IsBound())
    {
        OnDragStatusDelegate.Broadcast(bIsDragging);
    }
}
