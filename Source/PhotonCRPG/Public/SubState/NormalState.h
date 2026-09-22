// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubState/SubStateBase.h"
#include "NormalState.generated.h"

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UNormalState : public USubStateBase
{
	GENERATED_BODY()

public:

	virtual bool IsTriggeringDetect();
	virtual void MouseBeginClickAction();
	virtual void MouseTriggeringAction();
	virtual void MouseEndClickAction();
};
