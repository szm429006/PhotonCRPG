// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "SubSystem/DataSystem.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "AttributeSetBase.generated.h"

class ACharacterBase;
struct FGearData;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	TObjectPtr<ACharacterBase> Owner;

public:

	virtual void DoInitialize();

	virtual void ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData);

	virtual void GearChange(const FGearData& InGear, const bool bIsWear = true);
};
