// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnum.h"
#include "PhotonCRPG/Luban/Generated/schema.h"
#include "Function/DataFunc.h"
#include "UniversalDataStruct.generated.h"

/**
 * 
 */
class PHOTONCRPG_API UniversalDataStruct
{
public:
	UniversalDataStruct();
	~UniversalDataStruct();
};


USTRUCT(BlueprintType)
struct FInfoData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "名称")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "描述")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "物品", DisplayName = "图标")
	FString Icon;

	FInfoData()
		: Name("")
		, Description("")
		, Icon("")
	{
	}

	explicit FInfoData(const luban::SharedPtr<cfg::Uni::BasicInfo>& TableData)
		: Name(UDataFunc::StdToFString(TableData->name))
		, Description(UDataFunc::StdToFString(TableData->desc))
		, Icon(UDataFunc::StdToFString(TableData->icon))
	{}

	static FInfoData Set(const FInfoData& InInfo)
	{
		FInfoData Info;
		Info.Name = InInfo.Name;
		Info.Description = InInfo.Description;
		Info.Icon = InInfo.Icon;
		return Info;
	}
};

USTRUCT(BlueprintType)
struct FBasicAttrData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "基本属性", DisplayName = "血量")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "基本属性", DisplayName = "护甲")
	float ARP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "基本属性", DisplayName = "移动点")
	float AP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "基本属性", DisplayName = "行动点")
	float MP;

	FBasicAttrData()
		: HP(0)
		, ARP(0)
		, AP(0)
		, MP(0)
	{
	}

	explicit FBasicAttrData(const luban::SharedPtr<cfg::Attr::Basic>& TableData)
		: HP(TableData->hp)
		, ARP(TableData->arp)
		, AP(TableData->ap)
		, MP(TableData->mp)
	{}

	static FBasicAttrData Set(const FBasicAttrData& InAttr)
	{
		FBasicAttrData Attr;
		Attr.HP = InAttr.HP;
		Attr.ARP = InAttr.ARP;
		Attr.AP = InAttr.AP;
		Attr.MP = InAttr.MP;
		UE_LOG(LogTemp, Warning, TEXT("FBasicAttrData Set HP: %f, ARP: %f, AP: %f, MP: %f"), Attr.HP, Attr.ARP, Attr.AP, Attr.MP);
		return Attr;
	}

	void Add(const FBasicAttrData& InAttr, const float Multiplier = 1)
	{
		HP += InAttr.HP * Multiplier;
		ARP += InAttr.ARP * Multiplier;
		AP += InAttr.AP * Multiplier;
		MP += InAttr.MP * Multiplier;
	}

	TMap<FString, float> GetNonZeroProperties() const
	{
		TMap<FString, float> Result;
		
		for (TFieldIterator<FProperty> PropIt(StaticStruct()); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;
			if (const FFloatProperty* FloatProp = CastField<FFloatProperty>(Property))
			{
				const float Value = FloatProp->GetPropertyValue_InContainer(this);
				if (!FMath::IsNearlyZero(Value, 0.01f))
				{
					Result.Add(Property->GetName(), Value);
				}
			}
		}
		return Result;
	}
};

USTRUCT(BlueprintType)
struct FCoreAttrData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "核心属性", DisplayName = "力量")
	float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "核心属性", DisplayName = "敏捷")
	float Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "核心属性", DisplayName = "坚韧")
	float Toughness;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "核心属性", DisplayName = "感知")
	float Perception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "核心属性", DisplayName = "意志")
	float Willpower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "核心属性", DisplayName = "智力")
	float Intelligence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "核心属性", DisplayName = "社交")
	float Fellowship;

	FCoreAttrData()
		: Strength(0)
		, Agility(0)
		, Toughness(0)
		, Perception(0)
		, Willpower(0)
		, Intelligence(0)
		, Fellowship(0)
	{
	}

	explicit FCoreAttrData(const luban::SharedPtr<cfg::Attr::Core>& TableData)
		: Strength(TableData->strength)
		, Agility(TableData->agility)
		, Toughness(TableData->toughness)
		, Perception(TableData->perception)
		, Willpower(TableData->willpower)
		, Intelligence(TableData->intelligence)
		, Fellowship(TableData->fellowship)
	{}

	static FCoreAttrData Set(const FCoreAttrData& InAttr)
	{
		FCoreAttrData Attr;
		Attr.Strength = InAttr.Strength;
		Attr.Agility = InAttr.Agility;
		Attr.Toughness = InAttr.Toughness;
		Attr.Perception = InAttr.Perception;
		Attr.Willpower = InAttr.Willpower;
		Attr.Intelligence = InAttr.Intelligence;
		Attr.Fellowship = InAttr.Fellowship;
		return Attr;
	}

	void Add(const FCoreAttrData& InAttr, const float Multiplier = 1)
	{
		Strength += InAttr.Strength * Multiplier;
		Agility += InAttr.Agility * Multiplier;
		Toughness += InAttr.Toughness * Multiplier;
		Perception += InAttr.Perception * Multiplier;
		Willpower += InAttr.Willpower * Multiplier;
		Intelligence += InAttr.Intelligence * Multiplier;
		Fellowship += InAttr.Fellowship * Multiplier;
	}

	TMap<FString, float> GetNonZeroProperties() const
	{
		TMap<FString, float> Result;
		
		for (TFieldIterator<FProperty> PropIt(StaticStruct()); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;
			if (const FFloatProperty* FloatProp = CastField<FFloatProperty>(Property))
			{
				const float Value = FloatProp->GetPropertyValue_InContainer(this);
				if (!FMath::IsNearlyZero(Value, 0.01f))
				{
					Result.Add(Property->GetName(), Value);
				}
			}
		}
		return Result;
	}
};

USTRUCT(BlueprintType)
struct FBattleAttrData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "战斗属性", DisplayName = "伤害")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "战斗属性", DisplayName = "防御")
	float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "战斗属性", DisplayName = "移动速度")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "战斗属性", DisplayName = "暴击率")
	float Critical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "战斗属性", DisplayName = "命中率")
	float Hit;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "战斗属性", DisplayName = "闪避率")
	float Dodge;

	FBattleAttrData()
		: Attack(0)
		, Defence(0)
		, Speed(0)
		, Critical(0)
		, Hit(0)
		, Dodge(0)
	{
	}

	explicit FBattleAttrData(const luban::SharedPtr<cfg::Attr::Battle>& TableData)
		: Attack(TableData->attack)
		, Defence(TableData->defence)
		, Speed(TableData->speed)
		, Critical(TableData->critical)
		, Hit(TableData->hit)
		, Dodge(TableData->dodge)
	{}

	static FBattleAttrData Set(const FBattleAttrData& InAttr)
	{
		FBattleAttrData Attr;
		Attr.Attack = InAttr.Attack;
		Attr.Defence = InAttr.Defence;
		Attr.Speed = InAttr.Speed;
		Attr.Critical = InAttr.Critical;
		Attr.Hit = InAttr.Hit;
		Attr.Dodge = InAttr.Dodge;
		return Attr;
	}

	void Add(const FBattleAttrData& InAttr, const float Multiplier = 1)
	{
		Attack += InAttr.Attack * Multiplier;
		Defence += InAttr.Defence * Multiplier;
		Speed += InAttr.Speed * Multiplier;
		Critical += InAttr.Critical * Multiplier;
		Hit += InAttr.Hit * Multiplier;
		Dodge += InAttr.Dodge * Multiplier;
	}

	TMap<FString, float> GetNonZeroProperties() const
	{
		TMap<FString, float> Result;
		
		for (TFieldIterator<FProperty> PropIt(StaticStruct()); PropIt; ++PropIt)
		{
			FProperty* Property = *PropIt;
			if (const FFloatProperty* FloatProp = CastField<FFloatProperty>(Property))
			{
				const float Value = FloatProp->GetPropertyValue_InContainer(this);
				if (!FMath::IsNearlyZero(Value, 0.01f))
				{
					Result.Add(Property->GetName(), Value);
				}
			}
		}
		return Result;
	}
};


