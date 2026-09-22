// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/EquipComponent.h"
#include "Character/CharacterBase.h"
#include "Item/ArmorObject.h"
#include "Item/WeaponObject.h"
#include "SubSystem/DataSystem.h"
#include "SubSystem/InventorySystem.h"
#include "Function/DataFunc.h"
#include "Function/GlobalFunc.h"
#include "Interfaces/UnitComponentInterface.h"
#include "Data/ItemDataStruct.h"
#include "Item/ItemObject.h"
#include "UI/Inventory/InventorySlot.h"
#include "UI/Character/EquipmentSlot.h"
#include "Data/GlobalEnum.h"

// Sets default values for this component's properties
UEquipComponent::UEquipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UEquipComponent::DoInitialize()
{
	Owner = Cast<ACharacterBase>(GetOwner());
	if (!IsValid(Owner))
	{
		return;
	}

	const auto TbCharacterData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbCharacterData(Owner->GetCharacterID());
	if (TbCharacterData != nullptr)
	{
		for (const auto GearID : TbCharacterData->initGearList)
		{
			UE_LOG(LogTemp, Warning, TEXT("EquipComponent DoInitialize UGlobalFunc::GetSubsystem<UInventorySystem>()->CreateItem(%d)"), GearID);
			const auto Item = UGlobalFunc::GetSubsystem<UInventorySystem>()->CreateItem(GearID);
			if (IsValid(Item))
			{
				UE_LOG(LogTemp, Warning, TEXT("EquipComponent DoInitialize IsValid(Item)"));
				AutoEquip(Item);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("EquipComponent DoInitialize Finished..."));
}

void UEquipComponent::DoReset()
{
	IUnitComponentInterface::DoReset();
}

void UEquipComponent::DoDispose()
{
	Armors.Empty();
	Weapons.Empty();
}

ACharacterBase* UEquipComponent::GetCompOwner() const
{
	return Owner;
}

bool UEquipComponent::AutoEquip(UItemObject* Item)
{
	// UE_LOG(LogTemp, Warning, TEXT("EquipComponent AutoEquip"));
	if (Item->IsA(UArmorObject::StaticClass()))
	{
		// UE_LOG(LogTemp, Warning, TEXT("EquipComponent AutoEquip UArmorObject"));
		const auto Armor = Cast<UArmorObject>(Item);
		EquipArmor(Armor, Armor->GetArmorType());
		return true;
	}
	if (Item->IsA(UWeaponObject::StaticClass()))
	{
		// UE_LOG(LogTemp, Warning, TEXT("EquipComponent AutoEquip UWeaponObject"));
		const auto Weapon = Cast<UWeaponObject>(Item);
		EquipWeapon(Weapon, 0);
		return true;
	}
	// UE_LOG(LogTemp, Warning, TEXT("EquipComponent AutoEquip False"));
	return false;
}

void UEquipComponent::EquipToSlot(UInventorySlot* FromSlot, const UEquipmentSlot* ToSlot)
{
	switch (ToSlot->SlotType)
	{
	case EItemType::Armor:
		{
			const auto Armor = Cast<UArmorObject>(FromSlot->GetItem());
			EquipArmor(Armor, Armor->GetArmorType());
			// if (IsValid(Armor))
			// {
				
			// 	// UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipArmor Add : %d, Armor Count: %d"), Armor->GetArmorType(), Armors.Num());
			// }
		}
		break;
	case EItemType::Weapon:
		{
			if (FromSlot->IsA(UEquipmentSlot::StaticClass()))
			{
				SwapWeapon();
			}
			else
			{
				const auto Weapon = Cast<UWeaponObject>(FromSlot->GetItem());
				if (IsValid(Weapon))
				{
					EquipWeapon(Weapon, ToSlot->SlotIndex);
				}
			}
		}
		break;
	default:
		break;
	}
}

void UEquipComponent::UnEquipFromSlot(const UEquipmentSlot* Slot)
{
	switch (Slot->SlotType)
	{
	case EItemType::Armor:
		{
			const auto Armor = Cast<UArmorObject>(Slot->GetItem());
			Armors.Remove(Armor->GetArmorType());
			// 进行属性变换
			Owner->GearChange(Armor->GetGearData(), false);
			if (OnArmorChangeDelegate.IsBound())
			{
				OnArmorChangeDelegate.Broadcast(true);
			}
		}
		break;
	case EItemType::Weapon:
		{
			const auto Weapon = Cast<UWeaponObject>(Slot->GetItem());
			if (IsValid(Weapon))
			{
				if (Weapon->IsTwoHand())
				{
					Weapons.Empty();
				}
				else
				{
					Weapons.Remove(Slot->SlotIndex);
				}
				Owner->GearChange(Weapon->GetGearData(), false);
				
			}
			if (OnWeaponChangeDelegate.IsBound())
			{
				// UE_LOG(LogTemp, Warning, TEXT("EquipComponent UnEquipFromSlot UWeaponObject OnWeaponChangeDelegate.Broadcast(true)"));
				OnWeaponChangeDelegate.Broadcast(true);
			}
		}
		break;
	default:
		break;
	}
}

void UEquipComponent::EquipArmor(UArmorObject* Armor, const EArmorType ArmorType)
{
	// UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipArmor Armors Count: %d"), Armors.Num());
	const TObjectPtr<UArmorObject> CurSlotArmor = Armors.FindRef(ArmorType);
	if (IsValid(CurSlotArmor))
	{
		UGlobalFunc::GetSubsystem<UInventorySystem>()->AddItem(CurSlotArmor->GetItemID());
		// 进行属性变换
		UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipArmor CurSlotArmor->GearChange()"));
		Owner->GearChange(CurSlotArmor->GetGearData(), false);
	}

	Armors.Add(ArmorType, Armor);
	UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipArmor Add : %d, Armor Count: %d"), ArmorType, Armors.Num());
	// 进行属性变换
	Owner->GearChange(Armor->GetGearData(), true);
	UGlobalFunc::GetSubsystem<UInventorySystem>()->ReduceItem(Armor->GetItemID());
	// UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipArmor Finished..."));

	if (OnArmorChangeDelegate.IsBound())
	{
		OnArmorChangeDelegate.Broadcast(true);
	}
}

void UEquipComponent::EquipWeapon(UWeaponObject* Weapon, const uint8 SlotIndex)
{
	const auto AnthorSlotIndex = SlotIndex - 1 < 0 ? 1 : SlotIndex - 1;

	// UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipWeapon Weapons Count: %d"), Weapons.Num());
	if (Weapons.Num() > 0)
	{
		const TObjectPtr<UWeaponObject> CurSlotWeapon = Weapons.FindRef(SlotIndex);
		if (IsValid(CurSlotWeapon))
		{
			UGlobalFunc::GetSubsystem<UInventorySystem>()->AddItem(CurSlotWeapon->GetItemID());
			// 进行属性变换
			// UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipWeapon CurSlotWeapon->GearChange()"));
			Owner->GearChange(CurSlotWeapon->GetGearData(), false);

			if (CurSlotWeapon->IsTwoHand())
			{
				Weapons.Remove(AnthorSlotIndex);
				UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipWeapon AnthorSlotWeapon->Remove(%d)"), AnthorSlotIndex);
			}
		}
	}

	Weapons.Add(SlotIndex, Weapon);
	// 进行属性变换
	Owner->GearChange(Weapon->GetGearData(), true);
	// 双手武器
	UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipWeapon IsTwoHand: %s"), Weapon->IsTwoHand() ? TEXT("true") : TEXT("false"));
	if (Weapon->IsTwoHand())
	{
		const auto AnthorSlotWeapon = Weapons.FindRef(AnthorSlotIndex);
		if (IsValid(AnthorSlotWeapon))
		{
			UGlobalFunc::GetSubsystem<UInventorySystem>()->AddItem(AnthorSlotWeapon->GetItemID());
			// 进行属性变换
			// UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipWeapon AnthorSlotWeapon->GearChange()"));
			Owner->GearChange(AnthorSlotWeapon->GetGearData(), false);
		}
		Weapons.Add(AnthorSlotIndex, Weapon);
		// if (Weapons.Num() > 0)
		// {
			
		// }
	}
	UGlobalFunc::GetSubsystem<UInventorySystem>()->ReduceItem(Weapon->GetItemID());
	// UE_LOG(LogTemp, Warning, TEXT("EquipComponent EquipWeapon Finished..."));

	if (OnWeaponChangeDelegate.IsBound())
	{
		OnWeaponChangeDelegate.Broadcast(true);
	}
}

void UEquipComponent::SwapWeapon()
{
	const auto RHandWeapon = Weapons.FindRef(0);
	const auto LHandWeapon = Weapons.FindRef(1);
	if (IsValid(RHandWeapon))
	{
		Weapons.Add(1, RHandWeapon);
	}
	else
	{
		Weapons.Remove(1);
	}

	if (IsValid(LHandWeapon))
	{
		Weapons.Add(0, LHandWeapon);
	}
	else
	{
		Weapons.Remove(0);
	}

	if (OnWeaponChangeDelegate.IsBound())
	{
		OnWeaponChangeDelegate.Broadcast(true);
	}
}

