// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DiceSystem.generated.h"

enum class ECoreAttrType : uint8;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDiceSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	// 2D6 = 2个6面骰子，2D10、1D20，D = Dice
	UPROPERTY()
	TMap<uint8, float> ProbabilityMap_2D6;

public:

	virtual void Initialize(FSubSystemCollectionBase& Collection) override;

	// 获得掷骰子通过率
	float GetPassRate_2D6(const ECoreAttrType CoreAttrType, const uint8 Target);

	// 属性鉴定
	static bool GetCheckResult(const ECoreAttrType CoreAttrType, const uint8 Target);
};
