// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentSlot.h"
#include "UI/UIBase.h"
#include "Interfaces/InventoryInterface.h"
#include "CharacterUI.generated.h"

class UEquipmentSlot;
class UTextBlock;
class UVerticalBox;
class UWrapBox;
class UButton;
class UItemObject;
class UUserWidget;
class UInventorySlot;
class UMenuAnchor;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UCharacterUI : public UUIBase, public IInventoryInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UEquipmentSlot> UEquipmentSlotClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CharacterName;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> BasicAttrBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> CoreAttrBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> BattleAttrBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> EquipmentPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> WeaponPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> CloseBtn;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMenuAnchor> HoverAnchor;

protected:

	UPROPERTY()
	TObjectPtr<ACharacterBase> CurCharacter;

	UPROPERTY()
	TMap<FString, TObjectPtr<UTextBlock>> AttributeItemMap;

	UPROPERTY()
	TMap<uint8, TObjectPtr<UEquipmentSlot>> ArmorSlots;

	UPROPERTY()
	TArray<TObjectPtr<UEquipmentSlot>> WeaponSlots;

protected:

	UPROPERTY()
	TObjectPtr<UInventorySlot> HoverItemSlot;

	UPROPERTY()
	TObjectPtr<UItemObject> HoverItemData;

	FTimerHandle HoverTimerHandle;

protected:

	virtual void NativeOnInitialized() override;

	virtual void BindDelegates() override;

	virtual void UnbindDelegates() override;

public:

	virtual void DoLoad() override;

	virtual void DoUnload() override;

protected:

	UFUNCTION()
	void RefreshCharacterData(ACharacterBase* InCharacter);

	UFUNCTION()
	void RefreshArmor(const bool bRefreshAttr);

	UFUNCTION()
	void RefreshWeapon(const bool bRefreshAttr);

	void RefreshAttr();

private:

	UTextBlock* AddNewText();

	virtual UUserWidget* GetInfoPanel();

	virtual void ShowInfoPanel(UInventorySlot* HoverItem);

	virtual void HideInfoPanel();

	virtual void StartHoverTick();

	virtual void OnHovering();

	virtual void EndHoverTick();
};
