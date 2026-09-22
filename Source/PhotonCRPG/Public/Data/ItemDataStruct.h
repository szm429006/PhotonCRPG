// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnum.h"
#include "PhotonCRPG/Luban/Generated/schema.h"
#include "Data/UniversalDataStruct.h"
#include "Function/DataFunc.h"
#include "SubSystem/DataSystem.h"
#include "ItemDataStruct.generated.h"

/**
 * 
 */
class PHOTONCRPG_API ItemDataStruct
{
public:
	ItemDataStruct();
	~ItemDataStruct();
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "名称")
	// FString Name;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "描述")
	// FString Description;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "图标")
	// TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "类型")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "品质")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "重量")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "买入价")
	float BuyPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "卖出价")
	float SellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "可否堆叠")
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "最大堆叠数量")
	int32 MaxStack;

	FItemData()
		// : Name("")
		// , Description("")
		// , Icon(nullptr)
		: ItemType(EItemType::All)
		, ItemQuality(EItemQuality::Poor)
		, Weight(0)
		, BuyPrice(0)
		, SellPrice(0)
		, bIsStackable(false)
		, MaxStack(0)

	{
	}

	explicit FItemData(const luban::SharedPtr<cfg::Item::ItemData>& TableData)
		: ItemType(static_cast<EItemType>(TableData->type))
		, ItemQuality(static_cast<EItemQuality>(TableData->quality))
		, Weight(TableData->weight)
		, BuyPrice(TableData->buy)
		, SellPrice(TableData->sell)
		, bIsStackable(TableData->stackable)
		, MaxStack(TableData->maxStack)
	{}

	static FItemData Set(const FItemData& InItemData)
	{
		FItemData Item;
		// Item.Name = InItemData.Name;
		// Item.Description = InItemData.Description;
		// Item.Icon = InItemData.Icon;
		Item.ItemType = InItemData.ItemType;
		Item.ItemQuality = InItemData.ItemQuality;
		Item.Weight = InItemData.Weight;
		Item.BuyPrice = InItemData.BuyPrice;
		Item.SellPrice = InItemData.SellPrice;
		Item.bIsStackable = InItemData.bIsStackable;
		Item.MaxStack = InItemData.MaxStack;
		return Item;
	}
};

USTRUCT(BlueprintType)
struct FItemPack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品包", DisplayName = "ID")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品包", DisplayName = "数量")
	int32 Num;

	FItemPack()
		: ItemID(0)
		, Num(0)
	{
	}
};

USTRUCT(BlueprintType)
struct FGearData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "等级")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "穿戴等级")
	int32 LevelR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "模型路径")
	FString Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "插槽名称")
	FString Socket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "待机动画标签")
	FString IdleAnimTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "基本属性")
	FBasicAttrData BasicAttrData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "核心属性")
	FCoreAttrData CoreAttrData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "穿戴所需核心属性")
	FCoreAttrData CoreAttrR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "战斗属性")
	FBattleAttrData BattleAttrData;

	FGearData()
		: Level(0)
		, LevelR(0)
		, Model("")
		, Socket("")
		, IdleAnimTag("")
	{
	}

	explicit FGearData(const luban::SharedPtr<cfg::Item::WeaponTable>& TableData)
		: Level(TableData->level)
		, LevelR(TableData->levelR)
		, Model(UDataFunc::StdToFString(TableData->model))
		, Socket(UDataFunc::StdToFString(TableData->socket))
		, IdleAnimTag(UDataFunc::StdToFString(TableData->idleAnimTag))
		, BasicAttrData(FBasicAttrData(TableData->attrBasic))
		, CoreAttrData(FCoreAttrData(TableData->attrCore))
		, CoreAttrR(FCoreAttrData(TableData->attrCoreR))
		, BattleAttrData(FBattleAttrData(TableData->attrBattle))
	{}

	explicit FGearData(const luban::SharedPtr<cfg::Item::ArmorTable>& TableData)
		: Level(TableData->level)
		, LevelR(TableData->levelR)
		, Model("")
		, Socket("")
		, BasicAttrData(FBasicAttrData(TableData->attrBasic))
		, CoreAttrData(FCoreAttrData(TableData->attrCore))
		, CoreAttrR(FCoreAttrData(TableData->attrCoreR))
		, BattleAttrData(FBattleAttrData(TableData->attrBattle))
	{
	}

	static FGearData Set(const FGearData& InGearData)
	{
		FGearData Gear;
		Gear.Level = InGearData.Level;
		Gear.LevelR = InGearData.LevelR;
		Gear.Model = InGearData.Model;
		Gear.Socket = InGearData.Socket;
		Gear.IdleAnimTag = InGearData.IdleAnimTag;
		Gear.BasicAttrData = FBasicAttrData::Set(InGearData.BasicAttrData);
		Gear.CoreAttrData = FCoreAttrData::Set(InGearData.CoreAttrData);
		Gear.CoreAttrR = FCoreAttrData::Set(InGearData.CoreAttrR);
		Gear.BattleAttrData = FBattleAttrData::Set(InGearData.BattleAttrData);
		return Gear;
	}
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "基础伤害")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "范围")
	int32 Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "弹匣弹药")
	int32 ClipAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "最大弹药")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "射出弹药")
	int32 ShotAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "射速")
	float FireRate;

	FWeaponData()
		: BaseDamage(0.0f)
		, Range(0)
		, ClipAmmo(0)
		, MaxAmmo(0)
		, ShotAmmo(0)
		, FireRate(0.0f)
	{
	}

	explicit FWeaponData(const luban::SharedPtr<cfg::Item::WeaponTable>& TableData)
		: BaseDamage(TableData->baseDamage)
		, Range(TableData->range)
		, ClipAmmo(TableData->clipAmmo != nullptr ? *TableData->clipAmmo : 0)
		, MaxAmmo(TableData->maxAmmo != nullptr ? *TableData->maxAmmo : 0)
		, ShotAmmo(TableData->shotAmmo != nullptr ? *TableData->shotAmmo : 0)
		, FireRate(TableData->fireRate != nullptr ? *TableData->fireRate : 0.0f)
	{}

	static FWeaponData Set(const FWeaponData& InWeaponData)
	{
		FWeaponData Weapon;
		Weapon.BaseDamage = InWeaponData.BaseDamage;
		Weapon.Range = InWeaponData.Range;
		Weapon.ClipAmmo = InWeaponData.ClipAmmo;
		Weapon.MaxAmmo = InWeaponData.MaxAmmo;
		Weapon.ShotAmmo = InWeaponData.ShotAmmo;
		Weapon.FireRate = InWeaponData.FireRate;
		return Weapon;
	}
};
