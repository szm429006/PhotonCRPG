// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GlobalEventSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractFinishSignature);

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UGlobalEventSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnInteractFinishSignature OnInteractFinishDelegate;

public:

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "GlobalEventSystem")
	void BroadcastInteractFinish() const;
};
