// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubState/SubStateBase.h"
#include "BattlePrepareState.generated.h"

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UBattlePrepareState : public USubStateBase
{
	GENERATED_BODY()

public:

	virtual void StateInit(APhotonCRPGPlayerController* ControllerRef) override;

	virtual void StateEnd() override;
};
