// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Attribute/AttributeSetBase.h"
#include "Data/ItemDataStruct.h"
#include "SubSystem/DataSystem.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Data/GlobalEnum.h"
#include "CoreAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UCoreAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

public:
	UCoreAttributeSet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "力量")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Strength);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "敏捷")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Agility);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "坚韧")
	FGameplayAttributeData Toughness;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Toughness);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "感知")
	FGameplayAttributeData Perception;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Perception);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "意志")
	FGameplayAttributeData Willpower;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Willpower);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "智力")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Intelligence);
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "社交")
	FGameplayAttributeData Fellowship;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Fellowship);

public:

	virtual void ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GearChange(const FGearData& InGear, const bool bIsWear = true) override;

	UFUNCTION(BlueprintCallable, Category = "属性")
	FORCEINLINE float GetAttrValue(const ECoreAttrType AttrType) const
	{
		switch (AttrType)
		{
		case ECoreAttrType::Strength:
			return GetStrength();
		case ECoreAttrType::Agility:
			return GetAgility();
		case ECoreAttrType::Toughness:
			return GetToughness();
		case ECoreAttrType::Perception:
			return GetPerception();
		case ECoreAttrType::Willpower:
			return GetWillpower();
		case ECoreAttrType::Intelligence:
			return GetIntelligence();
		case ECoreAttrType::Fellowship:
			return GetFellowship();
		default:
			return 0.0f;
		}
	}

	UFUNCTION(BlueprintCallable, Category = "属性")
	FORCEINLINE void SetAttrValue(const ECoreAttrType AttrType, const float NewValue)
	{
		switch (AttrType)
		{
		case ECoreAttrType::Strength:
			SetStrength(NewValue);
			break;
		case ECoreAttrType::Agility:
			SetAgility(NewValue);
			break;
		case ECoreAttrType::Toughness:
			SetToughness(NewValue);
			break;
		case ECoreAttrType::Perception:
			SetPerception(NewValue);
			break;
		case ECoreAttrType::Willpower:
			SetWillpower(NewValue);
			break;
		case ECoreAttrType::Intelligence:
			SetIntelligence(NewValue);
			break;
		case ECoreAttrType::Fellowship:
			SetFellowship(NewValue);
			break;
		default:
			break;
		}
	}
};
