// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnum.generated.h"

/**
 * 
 */
class PHOTONCRPG_API GlobalEnum
{
public:
	GlobalEnum();
	~GlobalEnum();
};

UENUM(BlueprintType)
enum class EBasicAttrType : uint8
{
	HP = 0	UMETA(DisplayName = "血量"),
	ARP		UMETA(DisplayName = "护甲"),
	AP		UMETA(DisplayName = "行动点"),
	MP		UMETA(DisplayName = "移动点")
};
ENUM_RANGE_BY_FIRST_AND_LAST(EBasicAttrType, EBasicAttrType::HP, EBasicAttrType::MP);

UENUM(BlueprintType)
enum class ECoreAttrType : uint8
{
	Strength = 0	UMETA(DisplayName = "力量"),
	Agility			UMETA(DisplayName = "敏捷"),
	Toughness		UMETA(DisplayName = "坚韧"),
	Perception		UMETA(DisplayName = "感知"),
	Willpower		UMETA(DisplayName = "意志"),
	Intelligence	UMETA(DisplayName = "智力"),
	Fellowship		UMETA(DisplayName = "社交")
};
ENUM_RANGE_BY_FIRST_AND_LAST(ECoreAttrType, ECoreAttrType::Strength, ECoreAttrType::Fellowship);

UENUM(BlueprintType)
enum class EBattleAttrType : uint8
{
	Attack = 0		UMETA(DisplayName = "攻击力"),
	Defence			UMETA(DisplayName = "防御力"),
	Speed			UMETA(DisplayName = "速度"),
	Critical		UMETA(DisplayName = "暴击率"),
	Hit				UMETA(DisplayName = "命中率"),
	Dodge			UMETA(DisplayName = "闪避率")
};
ENUM_RANGE_BY_FIRST_AND_LAST(EBattleAttrType, EBattleAttrType::Attack, EBattleAttrType::Dodge);

UENUM()
enum class EItemType : uint8
{
	All = 0		UMETA(DisplayName = "全部"),
	Consumable	UMETA(DisplayName = "消耗品"),
	Weapon		UMETA(DisplayName = "武器"),
	Armor		UMETA(DisplayName = "护甲"),
	Prop		UMETA(DisplayName = "道具"),
	Collectable UMETA(DisplayName = "收集品"),
	Quest		UMETA(DisplayName = "任务物品"),
	Mundane		UMETA(DisplayName = "杂物"),
};

//FString ItemTypeName[] = {"全部", "消耗品", "武器", "护甲", "道具", "收集品", "任务物品", "杂物"};
ENUM_RANGE_BY_FIRST_AND_LAST(EItemType, EItemType::All, EItemType::Mundane);
//ENUM_RANGE_BY_COUNT(EItemType, EItemType::MunDane);

UENUM()
enum class EItemQuality : uint8
{
	Poor = 0		UMETA(DisplayName = "劣质"),
	Common			UMETA(DisplayName = "普通"),
	Good			UMETA(DisplayName = "优良"),
	Epic			UMETA(DisplayName = "史诗"),
	Lengendary		UMETA(DisplayName = "传说"),
};

UENUM()
enum class EGameStateType : uint8
{
	// 常规状态
	Normal = 0		UMETA(DisplayName = "常规"),
	Scenario	UMETA(DisplayName = "剧情"),

	// 作战状态
	BattlePrepare 	UMETA(DisplayName = "战斗准备"),
	PlayerBattle 	UMETA(DisplayName = "玩家行动"),
	AIBattle 		UMETA(DisplayName = "AI行动"),
	BattleEnd 		UMETA(DisplayName = "战斗结束"),
};

UENUM()
enum class EFactionType : uint8
{
	// 常规状态
	Player		UMETA(DisplayName = "玩家"),
	Enemy	UMETA(DisplayName = "敌人"),
	NPC 	UMETA(DisplayName = "NPC"),
	Null 	UMETA(hidden),
};

UENUM()
enum class EArmorType : uint8
{
	Helmet = 0	UMETA(DisplayName = "头盔"),
	Chest		UMETA(DisplayName = "胸甲"),
	Belt		UMETA(DisplayName = "腰带"),
	Leg			UMETA(DisplayName = "腿甲"),
	Shoe		UMETA(DisplayName = "鞋"),
	Trinket		UMETA(DisplayName = "饰品"),
	Null		UMETA(hidden),
};
ENUM_RANGE_BY_COUNT(EArmorType, EArmorType::Null);

UENUM()
enum class EWeaponType : uint8
{
	Pistol = 0	UMETA(DisplayName = "手枪"),
	Rifle		UMETA(DisplayName = "步枪"),
	SniperRifle	UMETA(DisplayName = "狙击枪"),
	Sword		UMETA(DisplayName = "剑"),
	Null		UMETA(hidden),
};
ENUM_RANGE_BY_COUNT(EWeaponType, EWeaponType::Null);

UENUM()
enum class EWeaponAtkType : uint8
{
	Ranged = 0	UMETA(DisplayName = "远程"),
	Close		UMETA(DisplayName = "近战"),
	SHand		UMETA(DisplayName = "副手")
};
