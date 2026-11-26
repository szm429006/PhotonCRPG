// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/BasicAttributeSet.h"
#include "SubSystem/DataSystem.h"
#include "GameplayEffectExtension.h"
#include "Data/GlobalTags.h"

UBasicAttributeSet::UBasicAttributeSet()
{
    InitHealth(0);
    InitMaxHealth(0);
    InitArmor(0);
    InitMaxArmor(0);
    InitAP(0);
    InitMaxAP(0);
    InitMP(0);
    InitMaxMP(0);
}

void UBasicAttributeSet::ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData)
{
    UE_LOG(LogTemp, Warning, TEXT("UBasicAttributeSet ReadDataFromTable() HP: %f, ARP: %f, AP: %f, MP: %f"),
    TbCharacterData->initAttrBasic->hp, TbCharacterData->initAttrBasic->arp, TbCharacterData->initAttrBasic->ap, TbCharacterData->initAttrBasic->mp);
    SetMaxHealth(GetMaxHealth() + TbCharacterData->initAttrBasic->hp);
    // SetHealth(GetHealth() + TbCharacterData->initAttrBasic->hp);
    SetHealth(GetMaxHealth());

    SetMaxArmor(GetMaxArmor() + TbCharacterData->initAttrBasic->arp);
    // SetArmor(GetArmor() + TbCharacterData->initAttrBasic->arp);
    SetArmor(GetMaxArmor());
    
    SetMaxAP(GetMaxAP() + TbCharacterData->initAttrBasic->ap);
    // SetAP(GetAP() + TbCharacterData->initAttrBasic->ap);
    SetAP(GetMaxAP());
    
    SetMaxMP(GetMaxMP() + TbCharacterData->initAttrBasic->mp);
    // SetMP(GetMP() + TbCharacterData->initAttrBasic->mp);
    SetMP(GetMaxMP());

    UE_LOG(LogTemp, Warning, TEXT("UBasicAttributeSet ReadDataFromTable() MAXHP: %f, MAXARMOR: %f, MAXAP: %f, MAXMP: %f"),
    GetMaxHealth(), GetMaxArmor(), GetMaxAP(), GetMaxMP());
}

void UBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
    else if (Attribute == GetArmorAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxArmor());
    }
    else if (Attribute == GetAPAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxAP());
    }
    else if (Attribute == GetMPAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMP());
    }
}

void UBasicAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);
    if (Attribute == GetHealthAttribute() && NewValue <= 0.f)
    {
        // 执行死亡逻辑
        FGameplayTagContainer DeathTagContainer;
        DeathTagContainer.AddTag(GlobalTags::Ability_Death);
        GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(DeathTagContainer);
    }
}

void UBasicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute() || Data.EvaluatedData.Attribute == GetArmorAttribute())
    {
        // 处理生命值变化
    }

    // 伤害计算
}

void UBasicAttributeSet::GearChange(const FGearData& InGear, const bool bIsWear)
{
    // UE_LOG(LogTemp, Warning, TEXT("UBasicAttributeSet GearChange MAXHealth: %f"), GetMaxHealth() + (bIsWear ? InGear.BasicAttrData.HP * 1 : InGear.BasicAttrData.HP * -1));
    SetMaxHealth(GetMaxHealth() + (bIsWear ? InGear.BasicAttrData.HP * 1 : InGear.BasicAttrData.HP * -1));
    // UE_LOG(LogTemp, Warning, TEXT("UBasicAttributeSet GearChange Health: %f"), GetHealth());    
    SetHealth(GetMaxHealth());

    SetMaxArmor(GetMaxArmor() + (bIsWear ? InGear.BasicAttrData.ARP * 1 : InGear.BasicAttrData.ARP * -1));
    SetArmor(GetMaxArmor());
    
    SetMaxAP(GetMaxAP() + (bIsWear ? InGear.BasicAttrData.AP * 1 : InGear.BasicAttrData.AP * -1));
    SetAP(GetMaxAP());
    
    SetMaxMP(GetMaxMP() + (bIsWear ? InGear.BasicAttrData.MP * 1 : InGear.BasicAttrData.MP * -1));
    SetMP(GetMaxMP());
}
