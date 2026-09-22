// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ArmorObject.h"
#include "Data/GlobalEnum.h"
#include "SubSystem/DataSystem.h"
#include "Data/ItemDataStruct.h"
#include "Function/GlobalFunc.h"
#include "Data/GlobalEnum.h"
#include "Data/UniversalDataStruct.h"


void UArmorObject::Initialize(const int32 InItemID)
{
    Super::Initialize(InItemID);
    
    const luban::SharedPtr<cfg::Item::ArmorTable> TbArmorData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbArmorData(InItemID);
    if (TbArmorData)
    {
        GearData = FGearData(TbArmorData);
        ArmorType = static_cast<EArmorType>(TbArmorData->type);
    }
}
