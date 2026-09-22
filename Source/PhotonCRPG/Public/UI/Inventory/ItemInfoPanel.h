// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "UI/UIBase.h"
#include "ItemInfoPanel.generated.h"

class UItemObject;
class UImage;
class UTextBlock;
class UVerticalBox;
class USpacer;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UItemInfoPanel : public UUIBase
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TypeText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> QualityText;
		
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DescText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> WeightText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> BuyText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SellText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> AttrBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USpacer> AttrSpacer;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> WeaponInfoBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DamageText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> RangeText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> AmmoText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> FireRateText;

	UPROPERTY()
	TObjectPtr<UItemObject> Item;

	UPROPERTY()
	TArray<TObjectPtr<UTextBlock>> AttrTextItems;

public:

	void RefreshData(const UItemObject* ItemData);

private:

	UTextBlock* AddNewText();
};
