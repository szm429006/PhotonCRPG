// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GlobalEnum.h"
#include "Interfaces/UnitComponentInterface.h"
#include "EquipComponent.generated.h"

class UArmorObject;
class UWeaponObject;
class UItemObject;
class ACharacterBase;
class IUnitComponentInterface;
struct FGearData;
enum class EArmorType : uint8;
class UInventorySlot;
class UEquipmentSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArmorChangeSignature, const bool, bRefreshAttr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponChangeSignature, const bool, bRefreshAttr);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOTONCRPG_API UEquipComponent : public UActorComponent, public IUnitComponentInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipComponent();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据", DisplayName = "护甲列表")
	TMap<EArmorType, TObjectPtr<UArmorObject>> Armors;

	// 右手 0，左手 1
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "数据", DisplayName = "武器列表")
	TMap<uint8, TObjectPtr<UWeaponObject>> Weapons;

	UPROPERTY()
	TObjectPtr<ACharacterBase> Owner;


public:

	UPROPERTY(BlueprintAssignable)
	FArmorChangeSignature OnArmorChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FWeaponChangeSignature OnWeaponChangeDelegate;

public:

	virtual void DoInitialize() override;

	virtual void DoReset() override;

	virtual void DoDispose() override;

	virtual ACharacterBase* GetCompOwner() const override;

	// 自动装备物品：用于初始化，以及在背包界面中双击某个物品时
	bool AutoEquip(UItemObject* Item);

	void EquipToSlot(UInventorySlot* FromSlot, const UEquipmentSlot* ToSlot); 

	void UnEquipFromSlot(const UEquipmentSlot* Slot);

	// 穿戴护甲
	void EquipArmor(UArmorObject* Armor, const EArmorType ArmorType);

	// 装备武器
	void EquipWeapon(UWeaponObject* Weapon, const uint8 SlotIndex);

	void SwapWeapon();

	FORCEINLINE TMap<EArmorType, TObjectPtr<UArmorObject>> GetArmors() const { return Armors; }

	FORCEINLINE TMap<uint8, TObjectPtr<UWeaponObject>> GetWeapons() const { return Weapons; }
};
