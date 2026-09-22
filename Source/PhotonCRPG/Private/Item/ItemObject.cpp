// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemObject.h"
#include "SubSystem/DataSystem.h"
#include "Function/GlobalFunc.h"

void UItemObject::Initialize(const int32 InItemID)
{
	const luban::SharedPtr<cfg::Item::ItemTable> TbItemData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbItemData(InItemID);
	if (TbItemData != nullptr)
	{
		ID = TbItemData->id;
		InfoData = FInfoData(TbItemData->basicInfo);
		const luban::SharedPtr<cfg::Item::ItemData> itemData = TbItemData->itemData;
		Data = FItemData(itemData);
	}
}
