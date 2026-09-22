// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Attribute/AttributeSetBase.h"
#include "SubSystem/DataSystem.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Data/ItemDataStruct.h"
#include "Data/GlobalEnum.h"
#include "BattleAttributeSet.generated.h"

struct FGearData;
enum class EBattleAttrType : uint8;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UBattleAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UBattleAttributeSet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "攻击")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UBattleAttributeSet, Attack);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "防御")
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UBattleAttributeSet, Defence);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "速度")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UBattleAttributeSet, Speed);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "暴击率")
	FGameplayAttributeData Critical;
	ATTRIBUTE_ACCESSORS(UBattleAttributeSet, Critical);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "命中率")
	FGameplayAttributeData Hit;
	ATTRIBUTE_ACCESSORS(UBattleAttributeSet, Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "闪避率")
	FGameplayAttributeData Dodge;
	ATTRIBUTE_ACCESSORS(UBattleAttributeSet, Dodge);

public:

	virtual void ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GearChange(const FGearData& InGear, const bool bIsWear = true) override;

	UFUNCTION(BlueprintCallable, Category = "属性")
	FORCEINLINE float GetAttrValue(EBattleAttrType AttrType) const
	{
		switch (AttrType)
		{
		case EBattleAttrType::Attack:
			return GetAttack();
		case EBattleAttrType::Defence:
			return GetDefence();
		case EBattleAttrType::Speed:
			return GetSpeed();
		case EBattleAttrType::Critical:
			return GetCritical();
		case EBattleAttrType::Hit:
			return GetHit();
		case EBattleAttrType::Dodge:
			return GetDodge();
		default:
			return 0.0f;
		}
	}

	UFUNCTION(BlueprintCallable, Category = "属性")
	FORCEINLINE void SetAttrValue(EBattleAttrType AttrType, const float NewValue)
	{
		switch (AttrType)
		{
		case EBattleAttrType::Attack:
			SetAttack(NewValue);
			break;
		case EBattleAttrType::Defence:
			SetDefence(NewValue);
			break;
		case EBattleAttrType::Speed:
			SetSpeed(NewValue);
			break;
		case EBattleAttrType::Critical:
			SetCritical(NewValue);
			break;
		case EBattleAttrType::Hit:
			SetHit(NewValue);
			break;
		case EBattleAttrType::Dodge:
			SetDodge(NewValue);
			break;
		default:
			break;
		}
	}
};
