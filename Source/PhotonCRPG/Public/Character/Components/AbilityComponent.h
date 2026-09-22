// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/UnitComponentInterface.h"
#include "AbilityComponent.generated.h"

class ACharacterBase;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UAbilityComponent : public UAbilitySystemComponent, public IUnitComponentInterface
{
	GENERATED_BODY()

public:

	UAbilityComponent();

public:

	UPROPERTY()
	TObjectPtr<ACharacterBase> Owner;

public:

	virtual void DoInitialize() override;

	virtual void DoReset() override;

	virtual void DoDispose() override;

	virtual ACharacterBase* GetCompOwner() const override;
};
