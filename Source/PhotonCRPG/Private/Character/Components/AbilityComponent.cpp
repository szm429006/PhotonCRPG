// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/AbilityComponent.h"
#include "Character/CharacterBase.h"

UAbilityComponent::UAbilityComponent()
{
    
}

void UAbilityComponent::DoInitialize()
{
    Owner = Cast<ACharacterBase>(GetOwner());
    InitAbilityActorInfo(GetOwner(), GetOwner());
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
