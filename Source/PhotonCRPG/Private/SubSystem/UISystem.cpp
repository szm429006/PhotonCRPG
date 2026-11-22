// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/UISystem.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "ArticyPackage.h"
#include "ArticyTypeSystem.h"
#include "ArticyDatabase.h"
#include "ArticyGlobalVariables.h"

UUISystem::UUISystem()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetInventoryClass(TEXT("/Game/Widget/WBP_InventoryUI.WBP_InventoryUI_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetGameClass(TEXT("/Game/Widget/WBP_GameUI.WBP_GameUI_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetDialogueClass(TEXT("/Game/Widget/WBP_DialogueUI.WBP_DialogueUI_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetContainerClass(TEXT("/Game/Widget/WBP_ContainerUI.WBP_ContainerUI_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetCharacterClass(TEXT("/Game/Widget/WBP_CharacterUI.WBP_CharacterUI_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetItemInfoClass(TEXT("/Game/Widget/WBP_ItemInfoPanel.WBP_ItemInfoPanel_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetUniversalUITriggerClass(TEXT("/Game/Widget/WBP_UniversalUITrigger.WBP_UniversalUITrigger_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetContainerSlotClass(TEXT("/Game/Widget/Inventory/WBP_ContainerSlot.WBP_ContainerSlot_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetDragItemClass(TEXT("/Game/Widget/Inventory/WBP_DragItem.WBP_DragItem_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetDropAreaClass(TEXT("/Game/Widget/Inventory/WBP_DropArea.WBP_DropArea_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetInventorySlotClass(TEXT("/Game/Widget/Inventory/WBP_InventorySlot.WBP_InventorySlot_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetItemTypeToggleClass(TEXT("/Game/Widget/Inventory/WBP_ItemTypeToggle.WBP_ItemTypeToggle_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetEquipmentSlotClass(TEXT("/Game/Widget/Character/WBP_EquipmentSlot.WBP_EquipmentSlot_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetDialogueItemClass(TEXT("/Game/Widget/Dialogue/WBP_DialogueItem.WBP_DialogueItem_C"));
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetDialogueOptionClass(TEXT("/Game/Widget/Dialogue/WBP_DialogueOption.WBP_DialogueOption_C"));

    // 图标
    static ConstructorHelpers::FObjectFinder<UTexture2D> BootsIconClass(TEXT("/Game/ArtAssets/Icon/Boots.Boots"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> GunIconClass(TEXT("/Game/ArtAssets/Icon/Gun.Gun"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> Gun02IconClass(TEXT("/Game/ArtAssets/Icon/Gun02.Gun02"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> Potion01IconClass(TEXT("/Game/ArtAssets/Icon/Potion01.Potion01"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> GranadeIconClass(TEXT("/Game/ArtAssets/Icon/Granade.Granade"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> SwordIconClass(TEXT("/Game/ArtAssets/Icon/Sword.Sword"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> Rifle02IconClass(TEXT("/Game/ArtAssets/Icon/Rifle02.Rifle02"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> RifleIconClass(TEXT("/Game/ArtAssets/Icon/Rifle.Rifle"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> HelmetIconClass(TEXT("/Game/ArtAssets/Icon/Helmet.Helmet"));
    static ConstructorHelpers::FObjectFinder<UTexture2D> ChestArmorIconClass(TEXT("/Game/ArtAssets/Icon/ChestArmor.ChestArmor"));


    // 模型
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SwordMeshClass(TEXT("/Game/Models/Sword003/sword002.sword002"));

    // 对话
    static ConstructorHelpers::FObjectFinder<UArticyPackage> DialoguePackageClass(TEXT("/Game/ArticyContent/Generated/Packages/All_objects.All_objects"));
    static ConstructorHelpers::FObjectFinder<UArticyTypeSystem> DialogueTypeSystemClass(TEXT("/Game/ArticyContent/Generated/PhotoncrpggTypeSystem.PhotoncrpggTypeSystem"));
    static ConstructorHelpers::FObjectFinder<UArticyDatabase> DialogueDatabaseClass(TEXT("/Game/ArticyContent/Generated/PhotoncrpggDatabase.PhotoncrpggDatabase"));
    static ConstructorHelpers::FObjectFinder<UArticyGlobalVariables> DialogueGlobalVariablesClass(TEXT("/Game/ArticyContent/Generated/PhotoncrpggGlobalVariables.PhotoncrpggGlobalVariables"));
}
