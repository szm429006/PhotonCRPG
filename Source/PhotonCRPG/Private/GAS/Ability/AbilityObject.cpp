// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/AbilityObject.h"
#include "Character/Components/AbilityComponent.h"

void UAbilityObject::Initialize(UAbilityComponent* OwnerComp, const FString& AbilityID, const FGameplayAbilitySpecHandle& Handle,
		const luban::SharedPtr<cfg::Gameplay::AbilityTable>& AbilityTable)
{
    OwnerAbilityComp = OwnerComp;
    ID = AbilityID;
    AbilitySpecHandle = Handle;
    InfoData = FInfoData(AbilityTable->basicInfo);
    AbilityData = FAbilityData(AbilityTable);
}
