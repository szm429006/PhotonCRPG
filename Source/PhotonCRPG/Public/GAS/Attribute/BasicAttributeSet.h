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
#include "BasicAttributeSet.generated.h"

struct FGameplayAttribute;
struct FGameplayEffectModCallbackData;
struct FGearData;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UBasicAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()
	
public:
	UBasicAttributeSet();

	// 血量
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "血量")
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "最大血量")
	FGameplayAttributeData MaxHealth;

	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MaxHealth);

	// 护甲
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "护甲")
	FGameplayAttributeData Armor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "最大护甲")
	FGameplayAttributeData MaxArmor;

	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MaxArmor);

	// 行动点 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "行动点")
	FGameplayAttributeData AP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "最大行动点")
	FGameplayAttributeData MaxAP;

	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, AP);
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MaxAP);

	// 移动点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "移动点")
	FGameplayAttributeData MP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "属性", DisplayName = "最大移动点")
	FGameplayAttributeData MaxMP;

	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MP);
	ATTRIBUTE_ACCESSORS(UBasicAttributeSet, MaxMP);

public:

	virtual void ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GearChange(const FGearData& InGear, const bool bIsWear = true) override;

	UFUNCTION(BlueprintCallable, Category = "属性")
	FORCEINLINE float GetAttrValue(const EBasicAttrType AttrType) const
	{
		switch (AttrType)
		{
		case EBasicAttrType::HP:
			return GetHealth();
		case EBasicAttrType::ARP:
			return GetArmor();
		case EBasicAttrType::AP:
			return GetAP();
		case EBasicAttrType::MP:
			return GetMP();
		default:
			return 0.0f;
		}
	}

	UFUNCTION(BlueprintCallable, Category = "属性")
	FORCEINLINE void SetAttrValue(const EBasicAttrType AttrType, const float NewValue)
	{
		switch (AttrType)
		{
		case EBasicAttrType::HP:
			SetHealth(NewValue);
			break;
		case EBasicAttrType::ARP:
			SetArmor(NewValue);
			break;
		case EBasicAttrType::AP:
			SetAP(NewValue);
			break;
		case EBasicAttrType::MP:
			SetMP(NewValue);
			break;
		default:
			break;
		}
	}
};
