// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemContainer.h"
#include "Item/ItemObject.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/InventorySystem.h"
#include "UI/Inventory/ContainerUI.h"
#include "SubSystem/UISystem.h"
#include "Interfaces/InteractInterface.h"
#include "Character/Components/InteractComponent.h"

// Sets default values
AItemContainer::AItemContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	InteractComp = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComp"));
	InteractComp->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AItemContainer::BeginPlay()
{
	Super::BeginPlay();
	
	// 初始化所有物品包的信息，并加入容器
	for (const FItemPack& ItemPack : ItemPacks) 
	{
		UItemObject* Item = UGlobalFunc::GetSubsystem<UInventorySystem>()->CreateItem(ItemPack.ItemID);
		
		if (IsValid(Item))
		{
			Item->Num = ItemPack.Num;
			ContainedItems.Add(Item);
		}	
	}
}

void AItemContainer::AddItem(const int32 ItemID, const int32 Num)
{
	const TObjectPtr<UItemObject>* CurItem = nullptr;
    if (ContainedItems.Num() > 0)
    {
        CurItem = ContainedItems.FindByPredicate([ItemID](const UItemObject* ArrayItem)
        {
            return ArrayItem->GetItemID() == ItemID;
        });
    }

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
			ContainedItems.Remove(CurItemRef);
		}
		return;
	}
	if (Num > 0)
	{
		const TObjectPtr<UItemObject> NewItem = UGlobalFunc::GetSubsystem<UInventorySystem>()->CreateItem(ItemID);
        if (!IsValid(NewItem))
        {
            //UE_LOG(LogTemp, Warning, TEXT("创建物品失败"));
            return;
        }
		NewItem->Num = Num;
		ContainedItems.Add(NewItem);
		return;
	}
}
	
void AItemContainer::RemoveAll()
{
	if (ContainedItems.Num() > 0)
	{
		for (const TObjectPtr<UItemObject>& Item : ContainedItems)
		{
			UGlobalFunc::GetSubsystem<UInventorySystem>()->AddItem(Item->GetItemID(), Item->Num, false);
		}
		ContainedItems.Empty();
		UGlobalFunc::GetSubsystem<UInventorySystem>()->BroadCastItemChange();
	}
}

// Called every frame
// void AItemContainer::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);

// }

void AItemContainer::MakeInteraction()
{
    IInteractInterface::MakeInteraction();
	UGlobalFunc::GetSubsystem<UUISystem>()->LoadUI<UContainerUI>()->ShowItems(this);
}
