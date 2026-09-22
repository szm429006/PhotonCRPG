// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ItemTypeToggle.h"
#include "../PhotonCRPG.h"
#include "Function/GlobalFunc.h"
#include "Data/GlobalEnum.h"
#include "SubSystem/DataSystem.h"
#include "Data/ItemDataStruct.h"

void UItemTypeToggle::RefreshData(const EItemType InItemType)
{
    ItemType = InItemType;
    // SetText(ItemTypeName[static_cast<uint8>(InItemType)]);

    SetText(UGlobalFunc::GetLocNameByEnum<EItemType>(InItemType));
}

