// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/GearObject.h"
#include "WeaponObject.generated.h"

struct FWeaponData;
enum class EWeaponType : uint8;
enum class EWeaponAtkType : uint8;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UWeaponObject : public UGearObject
{
	GENERATED_BODY()

protected:

	EWeaponType WeaponType;

	EWeaponAtkType AtkType;

	bool bIsTwoHand;

	FWeaponData WeaponData;

	TArray<FString> AbilityArray;

	int32 CurAmmo;

public:

	virtual void Initialize(const int32 InItemID) override;

	UFUNCTION(BlueprintCallable, Category = "装备系统", DisplayName = "获取武器类型")
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

	UFUNCTION(BlueprintCallable, Category = "装备系统", DisplayName = "获取武器攻击类型")
	FORCEINLINE EWeaponAtkType GetAtkType() const { return AtkType; }

	UFUNCTION(BlueprintCallable, Category = "装备系统", DisplayName = "是否双持")
	FORCEINLINE bool IsTwoHand() const { return bIsTwoHand; }

	UFUNCTION(BlueprintCallable, Category = "装备系统", DisplayName = "获取武器数据")
	FORCEINLINE FWeaponData GetWeaponData() const { return WeaponData; }

	UFUNCTION(BlueprintCallable, Category = "装备系统", DisplayName = "获取当前弹药")
	FORCEINLINE int32 GetCurAmmo() const { return CurAmmo; }

	UFUNCTION(BlueprintCallable, Category = "装备系统", DisplayName = "获取武器能力数组")
	FORCEINLINE TArray<FString> GetAbilityArray() const { return AbilityArray; }
};
