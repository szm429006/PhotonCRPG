// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Character/CharacterUI.h"
#include "Character/CharacterBase.h"
#include "Data/GlobalEnum.h"
#include "Function/GlobalFunc.h"
#include "Function/DataFunc.h"
#include "Data/UniversalDataStruct.h"
#include "Data/ItemDataStruct.h"
#include "SubSystem/DataSystem.h"
#include "GAS/Attribute/BasicAttributeSet.h"
#include "GAS/Attribute/CoreAttributeSet.h"
#include "GAS/Attribute/BattleAttributeSet.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "UI/Character/EquipmentSlot.h"
#include "Components/WrapBox.h"
#include "Character/Components/EquipComponent.h"
#include "UI/Inventory/InventorySlot.h"
#include "UI/Inventory/ItemInfoPanel.h"
#include "Components/MenuAnchor.h"
#include "Item/ItemObject.h"

void UCharacterUI::NativeOnInitialized()
{
    // 初始化属性栏
    for(const EBasicAttrType AttrType : TEnumRange<EBasicAttrType>())
    {
        const auto AttrItem = AddNewText();
        BasicAttrBox->AddChild(AttrItem);
        AttributeItemMap.Add(UDataFunc::GetEnumName<EBasicAttrType>(AttrType), AttrItem);
    }

    for(const ECoreAttrType AttrType : TEnumRange<ECoreAttrType>())
    {
        const auto AttrItem = AddNewText();
        CoreAttrBox->AddChild(AttrItem);
        AttributeItemMap.Add(UDataFunc::GetEnumName<ECoreAttrType>(AttrType), AttrItem);
    }

    for(const EBattleAttrType AttrType : TEnumRange<EBattleAttrType>())
    {
        const auto AttrItem = AddNewText();
        BattleAttrBox->AddChild(AttrItem);
        AttributeItemMap.Add(UDataFunc::GetEnumName<EBattleAttrType>(AttrType), AttrItem);
    }

    // 根据所有装备类型创建装备槽位
    for(const EArmorType ArmorType : TEnumRange<EArmorType>())
    {
        // UE_LOG(LogTemp, Warning, TEXT("CharacterUI NativeOnInitialized ArmorSlots Count: %d"), ArmorSlots.Num());
        const auto ArmorSlotItem = CreateWidget<UEquipmentSlot>(this, UEquipmentSlotClass);
        if (IsValid(ArmorSlotItem))
        {
            EquipmentPanel->AddChild(ArmorSlotItem);
            ArmorSlotItem->RefreshData(nullptr, 0);
            ArmorSlotItem->SetParent(this);

            // UE_LOG(LogTemp, Warning, TEXT("CharacterUI NativeOnInitialized ArmorSlotItem Add: %d"), ArmorSlots.Num());
            uint8 Index = static_cast<uint8>(ArmorType);
            ArmorSlotItem->SetSlotInfo(EItemType::Armor, Index);
            ArmorSlots.Add(Index, ArmorSlotItem);
        }        
    }

    // UE_LOG(LogTemp, Warning, TEXT("CharacterUI NativeOnInitialized WeaponSlots Count: %d"), WeaponSlots.Num());
    for(uint8 i = 0; i < 2; i++)
    {
        const auto WeaponSlotItem = CreateWidget<UEquipmentSlot>(this, UEquipmentSlotClass);
        // UE_LOG(LogTemp, Warning, TEXT("CharacterUI NativeOnInitialized WeaponSlotItem Add: %d"), i);
        if (IsValid(WeaponSlotItem))
        {
            EquipmentPanel->AddChild(WeaponSlotItem);   
            WeaponSlotItem->RefreshData(nullptr, 0);
            WeaponSlotItem->SetParent(this);

            WeaponSlotItem->SetSlotInfo(EItemType::Weapon, i);
            WeaponSlots.Add(WeaponSlotItem);
        }
    }

    Super::NativeOnInitialized();
}

void UCharacterUI::BindDelegates()
{
    CloseBtn->OnClicked.AddDynamic(this, &UCharacterUI::DoCloseAction);
    HoverAnchor->OnGetUserMenuContentEvent.BindDynamic(this, &UCharacterUI::GetInfoPanel);
}

void UCharacterUI::UnbindDelegates()
{
    CloseBtn->OnClicked.Clear();
    HoverAnchor->OnGetUserMenuContentEvent.Clear();
}

void UCharacterUI::DoLoad()
{
    Super::DoLoad();
    RefreshCharacterData(UGlobalFunc::GetController()->GetCurCharacter());
}

void UCharacterUI::DoUnload()
{
    Super::DoUnload();
    CurCharacter = nullptr;
}

void UCharacterUI::RefreshCharacterData(ACharacterBase* InCharacter)
{
    if (!IsValid(InCharacter) || CurCharacter == InCharacter)
    {
        return;
    }

    CurCharacter = InCharacter;
    CharacterName->SetText(FText::FromString(InCharacter->GetInfo().InfoData.Name));

    RefreshArmor(false);
    RefreshWeapon(false);
    RefreshAttr();

    const auto EquipComp = CurCharacter->GetEquipComp();
    if (IsValid(EquipComp))
    {
        EquipComp->OnArmorChangeDelegate.Clear();
        EquipComp->OnWeaponChangeDelegate.Clear();
        EquipComp->OnArmorChangeDelegate.AddDynamic(this, &UCharacterUI::RefreshArmor);
        EquipComp->OnWeaponChangeDelegate.AddDynamic(this, &UCharacterUI::RefreshWeapon);
    }
}

void UCharacterUI::RefreshArmor(const bool bRefreshAttr)
{
    if (!CurCharacter)
    {
        return;
    }

    if (ArmorSlots.Num() > 0)
    {
        for (const auto ArmorSlot : ArmorSlots)
        {
            ArmorSlot.Value->RefreshEquipInfo(CurCharacter->GetEquipComp());
        }
    }

    if (bRefreshAttr)
    {
        RefreshAttr();
    }
}

void UCharacterUI::RefreshWeapon(const bool bRefreshAttr)
{
    if (!CurCharacter)
    {
        return;
    }

    if (WeaponSlots.Num() > 0)
    {
        for (uint8 i = 0; i < 2; i++)
        {
            WeaponSlots[i]->RefreshEquipInfo(CurCharacter->GetEquipComp());
        }
    }

    if (bRefreshAttr)
    {
        RefreshAttr();
    }
}

void UCharacterUI::RefreshAttr()
{
    if (!IsValid(CurCharacter))
    {
        return;
    }

    const auto BasicAttributeSet = Cast<UBasicAttributeSet>(CurCharacter->GetAbilitySystemComponent()->GetAttributeSet(UBasicAttributeSet::StaticClass()));
    for(const EBasicAttrType AttrType : TEnumRange<EBasicAttrType>())
    {
        AttributeItemMap[UDataFunc::GetEnumName<EBasicAttrType>(AttrType)]->SetText(FText::Format(NSLOCTEXT("Common", "Attr", "{0}: {1}"),
            FText::FromString(UGlobalFunc::GetLocNameByEnum<EBasicAttrType>(AttrType)), BasicAttributeSet->GetAttrValue(AttrType)));
    }

    const auto CoreAttributeSet = Cast<UCoreAttributeSet>(CurCharacter->GetAbilitySystemComponent()->GetAttributeSet(UCoreAttributeSet::StaticClass()));
    for(const ECoreAttrType AttrType : TEnumRange<ECoreAttrType>())
    {
        AttributeItemMap[UDataFunc::GetEnumName<ECoreAttrType>(AttrType)]->SetText(FText::Format(NSLOCTEXT("Common", "Attr", "{0}: {1}"),
            FText::FromString(UGlobalFunc::GetLocNameByEnum<ECoreAttrType>(AttrType)), CoreAttributeSet->GetAttrValue(AttrType)));
    }

    const auto BattleAttributeSet = Cast<UBattleAttributeSet>(CurCharacter->GetAbilitySystemComponent()->GetAttributeSet(UBattleAttributeSet::StaticClass()));
    for(const EBattleAttrType AttrType : TEnumRange<EBattleAttrType>())
    {
        AttributeItemMap[UDataFunc::GetEnumName<EBattleAttrType>(AttrType)]->SetText(FText::Format(NSLOCTEXT("Common", "Attr", "{0}: {1}"),
            FText::FromString(UGlobalFunc::GetLocNameByEnum<EBattleAttrType>(AttrType)), BattleAttributeSet->GetAttrValue(AttrType)));
    }
}

UTextBlock* UCharacterUI::AddNewText()
{
    UTextBlock* Text = NewObject<UTextBlock>(this);

    // 设置字体大小
    FSlateFontInfo FontInfo = Text->GetFont();
    FontInfo.Size = 15;
    Text->SetFont(FontInfo);

    if (const auto TextSlot = Cast<UVerticalBoxSlot>(Text->Slot))
    {
        TextSlot->SetPadding(FMargin(0.0f, 2.0f, 0.0f, 2.0f));
    }
    return Text;
}

UUserWidget* UCharacterUI::GetInfoPanel()
{
    if (IsValid(HoverItemSlot))
    {
        const auto MenuWidget = CreateWidget(this, HoverAnchor->MenuClass);
        const auto InfoPanel = Cast<UItemInfoPanel>(MenuWidget);
        InfoPanel->RefreshData(HoverItemSlot->GetItem());
        return MenuWidget;
    }
    return nullptr;
}

void UCharacterUI::ShowInfoPanel(UInventorySlot* HoverItem)
{
    HoverItemSlot = HoverItem;
    HoverItemData = HoverItem->GetItem();
    IInventoryInterface::ShowInfoPanel(HoverItem);
    HoverAnchor->Open(false);
}

void UCharacterUI::HideInfoPanel()
{
    HoverItemSlot = nullptr;
    HoverItemData = nullptr;
    IInventoryInterface::HideInfoPanel();
    HoverAnchor->Close();
}

void UCharacterUI::StartHoverTick()
{
    IInventoryInterface::StartHoverTick();
    GetWorld()->GetTimerManager().SetTimer(HoverTimerHandle, this, &UCharacterUI::OnHovering, 0.5f/60.0f, true);
}

void UCharacterUI::OnHovering()
{
    IInventoryInterface::OnHovering();
    if (!IsValid(HoverItemSlot->GetItem()))
    {
        HideInfoPanel();
    }
    else if (HoverItemSlot->GetItem() != HoverItemData)
    {
        HoverItemData = HoverItemSlot->GetItem();
        HoverAnchor->Close();
        HoverAnchor->Open(false);
    }
}

void UCharacterUI::EndHoverTick()
{
    IInventoryInterface::EndHoverTick();
    GetWorld()->GetTimerManager().ClearTimer(HoverTimerHandle);
}

