// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/ItemInfoPanel.h"
#include "Function/GlobalFunc.h"
#include "Item/GearObject.h"
#include "Item/ItemObject.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Spacer.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/GlobalEnum.h"
#include "Item/WeaponObject.h"
#include "Item/ArmorObject.h"

void UItemInfoPanel::RefreshData(const UItemObject* ItemData)
{
    NameText->SetText(FText::FromString(ItemData->GetInfoData().Name));
    TypeText->SetText(FText::FromString(UGlobalFunc::GetLocNameByEnum(ItemData->GetItemData().ItemType)));
    QualityText->SetText(FText::FromString(UGlobalFunc::GetLocNameByEnum(ItemData->GetItemData().ItemQuality)));
    DescText->SetText(FText::FromString(ItemData->GetInfoData().Description));
    WeightText->SetText(FText::Format(NSLOCTEXT("Common", "Weight", "重量: {0}"), ItemData->GetItemData().Weight));
    BuyText->SetText(FText::Format(NSLOCTEXT("Common", "BuyPrice", "买入价: {0}"), ItemData->GetItemData().BuyPrice));
    SellText->SetText(FText::Format(NSLOCTEXT("Common", "SellPrice", "卖出价: {0}"), ItemData->GetItemData().SellPrice));
    const auto IconResource = UGlobalFunc::GetCachedIcon(ItemData->GetInfoData().Icon);
    if (IconResource)
    {
        Icon->SetBrushFromTexture(IconResource);
    }

    if (ItemData->IsA(UGearObject::StaticClass()))
    {
        const auto GearData = Cast<UGearObject>(ItemData);
        AttrBox->SetVisibility(ESlateVisibility::Visible);
        AttrSpacer->SetVisibility(ESlateVisibility::Visible);

        const auto BasicAttrData = GearData->GetGearData().BasicAttrData;
        const auto CoreAttrData = GearData->GetGearData().CoreAttrData;
        const auto BattleAttrData = GearData->GetGearData().BattleAttrData;

        uint8 Index = 0;

        for (const auto Property : BasicAttrData.GetNonZeroProperties())
        {
            if (Index >= AttrTextItems.Num())
            {
                AddNewText();
            }
            AttrTextItems[Index++]->SetText(FText::Format(NSLOCTEXT("Common", "Attr", "{0} + {1}"), FText::FromString(UGlobalFunc::GetLocName(Property.Key)),
                Property.Value));
        }

        for (const auto Property : CoreAttrData.GetNonZeroProperties())
        {
            if (Index >= AttrTextItems.Num())
            {
                AddNewText();
            }
            AttrTextItems[Index++]->SetText(FText::Format(NSLOCTEXT("Common", "Attr", "{0} + {1}"), FText::FromString(UGlobalFunc::GetLocName(Property.Key)),
                Property.Value));
        }

        for (const auto Property : BattleAttrData.GetNonZeroProperties())
        {
            if (Index >= AttrTextItems.Num())
            {
                AddNewText();
            }

            // 显示最小零位，最大两位

            FNumberFormattingOptions Options;
            Options.MinimumFractionalDigits = 0;
            Options.MaximumFractionalDigits = 2;
            
            AttrTextItems[Index++]->SetText(FText::Format(NSLOCTEXT("Common", "Attr", "{0} + {1}"), FText::FromString(UGlobalFunc::GetLocName(Property.Key)),
                FText::AsNumber(Property.Value, &Options)));
        }

        if (Index < AttrBox->GetChildrenCount())
        {
            const uint8 Dif = AttrBox->GetChildrenCount() - Index;
            for (uint8 i = 0; i < Index + Dif; i++)
            {
                AttrBox->GetChildAt(i)->SetVisibility(ESlateVisibility::Collapsed);
            }
        }

        if (ItemData->IsA(UWeaponObject::StaticClass()))
        {
            const auto WeaponData = Cast<UWeaponObject>(ItemData);
            WeaponInfoBox->SetVisibility(ESlateVisibility::Visible);
            TypeText->SetText(FText::FromString(UGlobalFunc::GetLocNameByEnum(WeaponData->GetWeaponType())));
            DamageText->SetText(FText::Format(NSLOCTEXT("Common", "BaseDamage", "基础伤害: {0}"), WeaponData->GetWeaponData().BaseDamage));
            RangeText->SetText(FText::Format(NSLOCTEXT("Common", "Range", "攻击范围: {0}"), WeaponData->GetWeaponData().Range));

            if (WeaponData->GetAtkType() == EWeaponAtkType::Ranged)
            {
                AmmoText->SetText(FText::Format(NSLOCTEXT("Common", "Ammo", "弹药: {0}"), WeaponData->GetWeaponData().ClipAmmo));
                FireRateText->SetText(FText::Format(NSLOCTEXT("Common", "FireRate", "射速: {0}"), WeaponData->GetWeaponData().FireRate));
                AmmoText->SetVisibility(ESlateVisibility::Visible);
                FireRateText->SetVisibility(ESlateVisibility::Visible);
            }
            else 
            {
                AmmoText->SetVisibility(ESlateVisibility::Collapsed);
                FireRateText->SetVisibility(ESlateVisibility::Collapsed);
            }
        }
        else
        {
            WeaponInfoBox->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
    else
    {
        AttrBox->SetVisibility(ESlateVisibility::Collapsed);
        AttrSpacer->SetVisibility(ESlateVisibility::Collapsed);
        WeaponInfoBox->SetVisibility(ESlateVisibility::Collapsed);
    }
}

UTextBlock* UItemInfoPanel::AddNewText()
{
    UTextBlock* Text = NewObject<UTextBlock>(this);

    AttrBox->AddChild(Text);
    AttrTextItems.Add(Text);

    // 设置字体大小
    FSlateFontInfo FontInfo = Text->GetFont();
    FontInfo.Size = 12;
    Text->SetFont(FontInfo);

    if (const auto TextSlot = Cast<UVerticalBoxSlot>(Text->Slot))
    {
        TextSlot->SetPadding(FMargin(0.0f, 2.0f, 0.0f, 5.0f));
    }
    return Text;
}
