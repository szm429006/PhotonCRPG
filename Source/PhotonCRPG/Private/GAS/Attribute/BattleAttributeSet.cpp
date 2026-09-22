// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/BattleAttributeSet.h"
#include "SubSystem/DataSystem.h"
#include "GameplayEffectExtension.h"
#include "Data/ItemDataStruct.h"
#include "Data/GlobalEnum.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

UBattleAttributeSet::UBattleAttributeSet()
{
    InitAttack(0);
    InitDefence(0);
    InitSpeed(0);
    InitCritical(0);
    InitHit(0);
    InitDodge(0);
}

void UBattleAttributeSet::ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData)
{
    SetAttack(GetAttack() + TbCharacterData->initAttrBattle->attack);
    SetDefence(GetDefence() + TbCharacterData->initAttrBattle->defence);
    SetSpeed(GetSpeed() + TbCharacterData->initAttrBattle->speed);
    SetCritical(GetCritical() + TbCharacterData->initAttrBattle->critical);
    SetHit(GetHit() + TbCharacterData->initAttrBattle->hit);
    SetDodge(GetDodge() + TbCharacterData->initAttrBattle->dodge);
}

void UBattleAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
}

void UBattleAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UBattleAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}

void UBattleAttributeSet::GearChange(const FGearData& InGear, const bool bIsWear)
{
    SetAttack(GetAttack() + (bIsWear ? InGear.BattleAttrData.Attack * 1 : InGear.BattleAttrData.Attack * -1));
    SetDefence(GetDefence() + (bIsWear ? InGear.BattleAttrData.Defence * 1 : InGear.BattleAttrData.Defence * -1));
    SetSpeed(GetSpeed() + (bIsWear ? InGear.BattleAttrData.Speed * 1 : InGear.BattleAttrData.Speed * -1));
    SetCritical(GetCritical() + (bIsWear ? InGear.BattleAttrData.Critical * 1 : InGear.BattleAttrData.Critical * -1));
    SetHit(GetHit() + (bIsWear ? InGear.BattleAttrData.Hit * 1 : InGear.BattleAttrData.Hit * -1));
    SetDodge(GetDodge() + (bIsWear ? InGear.BattleAttrData.Dodge * 1 : InGear.BattleAttrData.Dodge * -1));
}
