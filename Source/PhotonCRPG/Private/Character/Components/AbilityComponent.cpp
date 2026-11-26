// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/AbilityComponent.h"
#include "GAS/Ability/AbilityObject.h"
#include "Function/GlobalFunc.h"
#include "Function/DataFunc.h"
#include "SubSystem/DataSystem.h"
#include "GAS/Ability/AbilityBase.h"
#include "Character/CharacterBase.h"

UAbilityComponent::UAbilityComponent()
{
    
}

void UAbilityComponent::DoInitialize()
{
    Owner = Cast<ACharacterBase>(GetOwner());
    InitAbilityActorInfo(GetOwner(), GetOwner());

    const auto TbCharacterData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbCharacterData(Owner->GetCharacterID());
    if (TbCharacterData != nullptr)
    {
        for (const auto AbilityID : TbCharacterData->initAbilityList)
        {
            AddAbility(UDataFunc::StdToFString(AbilityID));
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("AbilityComponent DoInitialize Finished..."));
}

void UAbilityComponent::DoReset()
{
    IUnitComponentInterface::DoReset();
}

void UAbilityComponent::DoDispose()
{
    IUnitComponentInterface::DoDispose();
}

ACharacterBase* UAbilityComponent::GetCompOwner() const
{
	return Owner;
}

UAbilityObject* UAbilityComponent::AddAbility(const FString& AbilityID)
{
    if (AbilityPool.Contains(AbilityID))
    {
        return nullptr;
    }

    UAbilityObject* AbilityObject = LoadAbilityDataByID(AbilityID);
    if (IsValid(AbilityObject))
    {
        AbilityPool.Add(AbilityID, AbilityObject);
        return AbilityObject;
    }
    return nullptr;
}

UAbilityObject* UAbilityComponent::LoadAbilityDataByID(const FString& AbilityID)
{
    const auto TbAbilityData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbAbilityData(AbilityID);
    if (TbAbilityData != nullptr)
    {
        const FString AbilityClassName = UDataFunc::StdToFString(TbAbilityData->abilityBP);
        const auto AbilityClass = UGlobalFunc::LoadAbility<UAbilityBase>(AbilityClassName);
        if (IsValid(AbilityClass))
        {
            UAbilityObject* AbilityObject = NewObject<UAbilityObject>(this);
            const FGameplayAbilitySpecHandle Handle = GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, -1, AbilityObject));
            AbilityObject->Initialize(this, AbilityID, Handle, TbAbilityData);
            return AbilityObject;
        }
    }
    return nullptr;
}

