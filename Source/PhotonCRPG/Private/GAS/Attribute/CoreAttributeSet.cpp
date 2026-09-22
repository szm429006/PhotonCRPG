// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/CoreAttributeSet.h"
#include "SubSystem/DataSystem.h"
#include "GameplayEffectExtension.h"
#include "Data/ItemDataStruct.h"
#include "GAS/Attribute/BattleAttributeSet.h"

UCoreAttributeSet::UCoreAttributeSet()
{
    InitStrength(0);
    InitAgility(0);
    InitToughness(0);
    InitPerception(0);
    InitWillpower(0);
    InitIntelligence(0);
    InitFellowship(0);
}

void UCoreAttributeSet::ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData)
{
    SetStrength(GetStrength() + TbCharacterData->initAttrCore->strength);
    SetAgility(GetAgility() + TbCharacterData->initAttrCore->agility);
    SetToughness(GetToughness() + TbCharacterData->initAttrCore->toughness);
    SetPerception(GetPerception() + TbCharacterData->initAttrCore->perception);
    SetWillpower(GetWillpower() + TbCharacterData->initAttrCore->willpower);
    SetIntelligence(GetIntelligence() + TbCharacterData->initAttrCore->intelligence);
    SetFellowship(GetFellowship() + TbCharacterData->initAttrCore->fellowship);
}

void UCoreAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
}

void UCoreAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);

    if (Attribute == GetStrengthAttribute())
    {
        const float OldAttack = GetOwningAbilitySystemComponent()->GetNumericAttribute(UBattleAttributeSet::GetAttackAttribute());
        const float NewAttack = OldAttack + (NewValue - OldValue) * 2;
        GetOwningAbilitySystemComponent()->SetNumericAttributeBase(UBattleAttributeSet::GetAttackAttribute(), NewAttack);
    }
}

void UCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}

void UCoreAttributeSet::GearChange(const FGearData& InGear, const bool bIsWear)
{
    SetStrength(GetStrength() + (bIsWear ? InGear.CoreAttrData.Strength * 1 : InGear.CoreAttrData.Strength * -1));
    SetAgility(GetAgility() + (bIsWear ? InGear.CoreAttrData.Agility * 1 : InGear.CoreAttrData.Agility * -1));
    SetToughness(GetToughness() + (bIsWear ? InGear.CoreAttrData.Toughness * 1 : InGear.CoreAttrData.Toughness * -1));
    SetPerception(GetPerception() + (bIsWear ? InGear.CoreAttrData.Perception * 1 : InGear.CoreAttrData.Perception * -1));
    SetWillpower(GetWillpower() + (bIsWear ? InGear.CoreAttrData.Willpower * 1 : InGear.CoreAttrData.Willpower * -1));
    SetIntelligence(GetIntelligence() + (bIsWear ? InGear.CoreAttrData.Intelligence * 1 : InGear.CoreAttrData.Intelligence * -1));
    SetFellowship(GetFellowship() + (bIsWear ? InGear.CoreAttrData.Fellowship * 1 : InGear.CoreAttrData.Fellowship * -1));
}