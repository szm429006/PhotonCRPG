// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnum.h"
#include "Function/DataFunc.h"
#include "SubSystem/DataSystem.h"
#include "GameplayDataStruct.generated.h"

/**
 * 
 */
class PHOTONCRPG_API GameplayDataStruct
{
public:
	GameplayDataStruct();
	~GameplayDataStruct();
};

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "能力蓝图类")
	FString AbilityBPClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "能力标签")
	FString AbilityTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "消耗类型")
	EAbilityCostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "作用类型")
	EAbilityFuncType FuncType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "消耗点数")
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "冷却时间")
	int32 CD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "能力范围")
	int32 Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "基准数值")
	float BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "武器伤害倍数")
	float WeaponMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "由武器决定范围")
	bool bRangeByWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "是否显示在UI")
	bool bIsShowInUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "能力", DisplayName = "是否有弹药")
	bool bHasAmmo;

	FAbilityData()
		: AbilityBPClass(""),
		AbilityTag(""),
		CostType(EAbilityCostType::AP),
		FuncType(EAbilityFuncType::Null),
		Cost(0.0f),
		CD(0),
		Range(0),
		BaseValue(0.0f),
		WeaponMultiplier(1.0f),
		bRangeByWeapon(false),
		bIsShowInUI(false),
		bHasAmmo(false)
	{
	}

	explicit FAbilityData(const luban::SharedPtr<cfg::Gameplay::AbilityTable>& TableData)
		: AbilityBPClass(UDataFunc::StdToFString(TableData->abilityBP)),
		AbilityTag(UDataFunc::StdToFString(TableData->abilityTag)),
		CostType(static_cast<EAbilityCostType>(TableData->costType)),
		FuncType(static_cast<EAbilityFuncType>(TableData->funcType)),
		Cost(TableData->cost),
		CD(TableData->cd),
		Range(TableData->range),
		BaseValue(TableData->baseValue),
		WeaponMultiplier(TableData->weaponMultiplier),
		bRangeByWeapon(TableData->rangeByWeapon),
		bIsShowInUI(TableData->isShowInUI),
		bHasAmmo(TableData->hasAmmo)
	{
	}

	static FAbilityData Set(const FAbilityData& NewAbility)
	{
		FAbilityData AbilityData;
		AbilityData.AbilityBPClass = NewAbility.AbilityBPClass;
		AbilityData.AbilityTag = NewAbility.AbilityTag;
		AbilityData.CostType = NewAbility.CostType;
		AbilityData.FuncType = NewAbility.FuncType;
		AbilityData.Cost = NewAbility.Cost;
		AbilityData.CD = NewAbility.CD;
		AbilityData.Range = NewAbility.Range;
		AbilityData.BaseValue = NewAbility.BaseValue;
		AbilityData.WeaponMultiplier = NewAbility.WeaponMultiplier;
		AbilityData.bRangeByWeapon = NewAbility.bRangeByWeapon;
		AbilityData.bIsShowInUI = NewAbility.bIsShowInUI;
		AbilityData.bHasAmmo = NewAbility.bHasAmmo;
		return AbilityData;
	}
};
