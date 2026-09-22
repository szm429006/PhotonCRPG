// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemObject.h"
#include "Data/ItemDataStruct.h"
#include "GearObject.generated.h"

struct FGearData;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UGearObject : public UItemObject
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "装备", DisplayName = "装备数据")
	FGearData GearData;

public:

	FORCEINLINE FGearData GetGearData() const { return GearData; }
};
