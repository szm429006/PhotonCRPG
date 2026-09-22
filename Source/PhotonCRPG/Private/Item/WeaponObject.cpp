// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponObject.h"
#include "Data/ItemDataStruct.h"
#include "Function/GlobalFunc.h"
#include "Subsystem/DataSystem.h"
#include "Data/GlobalEnum.h"


void UWeaponObject::Initialize(const int32 InItemID)
{
    Super::Initialize(InItemID);

    const luban::SharedPtr<cfg::Item::WeaponTable> TbWeaponData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbWeaponData(InItemID);
    if (TbWeaponData != nullptr)
    {
        GearData = FGearData(TbWeaponData);
        WeaponType = static_cast<EWeaponType>(TbWeaponData->type);
        AtkType = static_cast<EWeaponAtkType>(TbWeaponData->atkType);
        bIsTwoHand = TbWeaponData->TwoHand;
        WeaponData = FWeaponData(TbWeaponData);

        if (AtkType == EWeaponAtkType::Ranged)
        {
            CurAmmo = WeaponData.ClipAmmo;
        }
    }
}

