// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Universal/UniversalToggle.h"
#include "ItemTypeToggle.generated.h"

enum class EItemType : uint8;
extern const FString ItemTypeName[];

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UItemTypeToggle : public UUniversalToggle
{
	GENERATED_BODY()

protected:
	EItemType ItemType;

public:

	void RefreshData(const EItemType InItemType);

	FORCEINLINE EItemType GetItemType() const { return ItemType; }

	bool operator==(const UItemTypeToggle* OtherToggle) const
	{ 
		return this->ItemType == OtherToggle->ItemType;
	}
};
