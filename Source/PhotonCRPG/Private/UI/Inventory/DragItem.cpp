// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/DragItem.h"
#include "Item/ItemObject.h"
#include "Components/Image.h"
#include "Function/GlobalFunc.h"

void UDragItem::SetContent(const UItemObject* InItem) const
{
    // const auto IconResource = LoadObject<UTexture2D>(nullptr, *InItem->GetInfoData().Icon);
    const auto IconResource = UGlobalFunc::GetCachedIcon(InItem->GetInfoData().Icon);
    if (IconResource != nullptr)
    {
        Icon->SetBrushFromTexture(IconResource);
        Icon->SetVisibility(ESlateVisibility::Visible);
    }
}
