// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Data/GlobalEnum.h"
#include "PhotonCRPGGameState.generated.h"

class USubStateBase;
// enum class EGameStateType : uint8;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API APhotonCRPGGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGameStateType CurGameStateType = EGameStateType::Normal;

	UPROPERTY()
	TObjectPtr<USubStateBase> CurSubState;

protected:

	virtual void BeginPlay() override;

public:

	void SetGameStateType(const EGameStateType Type);

	FORCEINLINE EGameStateType GetGameStateType() const { return CurGameStateType; }

	FORCEINLINE USubStateBase* GetSubState() const { return CurSubState; }
};
