// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <memory>
#include "PhotonCRPG/Luban/Generated/schema.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Function/DataFunc.h"
#include "DataSystem.generated.h"


/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDataSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	cfg::Tables GlobalTables;

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FORCEINLINE cfg::Tables GetGlobalTables() const { return GlobalTables; }

	FORCEINLINE luban::SharedPtr<cfg::Character::CharacterTable> GetTbCharacterData(const FString& CharacterID)
	{ return GlobalTables.TbCharacter.get(UDataFunc::FStringToStd(CharacterID)); }

	FORCEINLINE luban::SharedPtr<cfg::Item::ItemTable> GetTbItemData(const int32 ItemID) { return GlobalTables.TbItem.get(ItemID); }

	FORCEINLINE luban::SharedPtr<cfg::Item::ArmorTable> GetTbArmorData(const int32 ItemID) { return GlobalTables.TbArmor.get(ItemID); }

	FORCEINLINE luban::SharedPtr<cfg::Item::WeaponTable> GetTbWeaponData(const int32 ItemID) { return GlobalTables.TbWeapon.get(ItemID); }

	FORCEINLINE luban::SharedPtr<cfg::Uni::LocalizationTable> GetTbLocalizationData(const FString& LocalizationID)
	{ return GlobalTables.TbLocalization.get(UDataFunc::FStringToStd(LocalizationID)); }

	FORCEINLINE luban::SharedPtr<cfg::Gameplay::AbilityTable> GetTbAbilityData(const FString& AbilityID)
	{ return GlobalTables.TbAbility.get(UDataFunc::FStringToStd(AbilityID)); }
};
