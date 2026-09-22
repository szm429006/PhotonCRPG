// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ItemDataStruct.h"
#include "Data/UniversalDataStruct.h"
#include "ItemObject.generated.h"

/**
 *
 */
UCLASS()
class PHOTONCRPG_API UItemObject : public UObject
{
	GENERATED_BODY()

protected:
	// 物品ID
	int32 ID;

	// 基本信息
	FInfoData InfoData;

	// 物品信息
	FItemData Data;

public:

	// 物品数量
	int32 Num;

	// 初始化
	virtual void Initialize(const int32 InItemID);

	UFUNCTION(BlueprintCallable, Category = "背包系统")
	FORCEINLINE int32 GetItemID() const { return ID; }

	UFUNCTION(BlueprintCallable, Category = "背包系统")
	FORCEINLINE FInfoData GetInfoData() const { return InfoData; }

	UFUNCTION(BlueprintCallable, Category = "背包系统")
	FORCEINLINE FItemData GetItemData() const { return Data; }

	bool operator == (const UItemObject* OtherItem) const
	{
		return this->ID == OtherItem->ID;
	}
};
