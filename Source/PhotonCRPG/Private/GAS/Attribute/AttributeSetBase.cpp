// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Attribute/AttributeSetBase.h"
#include "SubSystem/DataSystem.h"
#include "Character/CharacterBase.h"
#include "Function/GlobalFunc.h"
#include "Data/GlobalEnum.h"
#include "Data/UniversalDataStruct.h"
#include "Data/ItemDataStruct.h"

// 初始化属性集
void UAttributeSetBase::DoInitialize()
{
    Owner = Cast<ACharacterBase>(GetOwningActor());

    const auto TbCharacterData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbCharacterData(Owner->GetCharacterID());
    if (TbCharacterData != nullptr)
    {
        ReadDataFromTable(TbCharacterData);
    }
}

void UAttributeSetBase::ReadDataFromTable(const luban::SharedPtr<cfg::Character::CharacterTable>& TbCharacterData)
{
}

void UAttributeSetBase::GearChange(const FGearData& InGear, const bool bIsWear)
{
}
