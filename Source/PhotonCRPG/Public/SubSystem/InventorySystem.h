// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/ItemDataStruct.h"
#include "InventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemChangeSignature, const int32, ItemID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemCollectSignature, const int32, ItemID, const int32, Num);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDragSignature, const bool bIsDragging);

class UItemObject;
//struct FItemData;
enum class EItemType : uint8;

USTRUCT()
struct FTypeItemHolder
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<UItemObject>> ItemArray;

	FTypeItemHolder()
	{
	}
};

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UInventorySystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	// 背包容器
	UPROPERTY()
	TMap<EItemType, FTypeItemHolder> Inventory;

	// UPROPERTY()
	// TObjectPtr<UDataTable> ItemDataTable;

public:

	// 物品变更委托
	UPROPERTY(BlueprintAssignable, Category = "背包系统")
	FItemChangeSignature OnItemChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "背包系统")
	FItemCollectSignature OnItemCollectDelegate;

	FOnDragSignature OnDragStatusDelegate;

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// 获取背包中所有的物品
	UFUNCTION(BlueprintCallable, Category = "背包系统")
	TArray<UItemObject*> GetAllItems();

	UFUNCTION(BlueprintCallable, Category = "背包系统")
	TArray<UItemObject*> GetItemsByType(const EItemType ItemType);

	// 根据数量添加某个物品进入背包
	UFUNCTION(BlueprintCallable, Category = "背包系统")
	UItemObject* AddItem(const int32 ItemID, const int32 Num = 1, const bool bAutoBroadCast = true);

	// 减少物品
	UFUNCTION(BlueprintCallable, Category = "背包系统")
	UItemObject* ReduceItem(const int32 ItemID, const int32 Num = 1, const bool bAutoBroadCast = true);

	// 收集物品
	UFUNCTION(BlueprintCallable, Category = "背包系统")
	void CollectItem(const int32 ItemID, const int32 Num = 1);

	// 在数据表中查找某个物品
	//FItemData* GetItemData(const int32 ItemID) const;

	// 查找物品类型
	UFUNCTION(BlueprintCallable, Category = "背包系统")
	EItemType GetItemType(const int32 ItemID) const;

	// 查找并获取某个物品
	UFUNCTION(BlueprintCallable, Category = "背包系统")
	UItemObject* GetItem(const int32 ItemID) const;

	// 根据ID获取某个物品的数量
	UFUNCTION(BlueprintCallable, Category = "背包系统")
	int32 GetItemNum(const int32 ItemID) const;

	// 根据ID创建物品
	UItemObject* CreateItem(const int32 ItemID) const;	

	UFUNCTION(BlueprintCallable, Category = "背包系统")
	void BroadCastItemChange() const;

	UFUNCTION(BlueprintCallable, Category = "背包系统")
	void BroadCastItemCollect(const int32 ItemID, const int32 Num = 1) const;

	UFUNCTION(BlueprintCallable, Category = "背包系统")
	void BroadCastOnDragStatus(const bool bIsDragging) const;
};
