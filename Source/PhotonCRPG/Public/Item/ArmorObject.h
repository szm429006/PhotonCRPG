// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/GearObject.h"
#include "ArmorObject.generated.h"

struct FArmorData;
struct FGearData;
enum class EArmorType : uint8;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UArmorObject : public UGearObject
{
	GENERATED_BODY()

protected:

	EArmorType ArmorType;

public:

	virtual void Initialize(const int32 InItemID) override;

	FORCEINLINE EArmorType GetArmorType() const { return ArmorType; }
};
