// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DiceSystem.h"


void UDiceSystem::Initialize(FSubSystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    TMap<uint8, uint8> ResultMatrix_2D6;
	// 初始化掷骰子通过率
	for (uint8 i = 1; i <= 6; i++)
	{
		for (uint8 j = 1; j <= 6; j++)
		{
			const uint8 Value = i + j;
            if (ResultMatrix_2D6.Contains(Value))
            {
                ResultMatrix_2D6.Add(Value, 0);
            }
            ResultMatrix_2D6.Add(Value, ++ResultMatrix_2D6[Value]);
		}
	}

    for (const auto Result : ResultMatrix_2D6)
    {
        ProbabilityMap_2D6.Add(Result.Key, Result.Value / 36.f);
        UE_LOG(LogTemp, Warning, TEXT("%d : %d - %f"), Result.Key, Result.Value, Result.Value / 36.f);
    }
}

float UDiceSystem::GetPassRate_2D6(const ECoreAttrType CoreAttrType, const uint8 Target)
{
    return ProbabilityMap_2D6[Target];
}

static bool UDiceSystem::GetCheckResult(const ECoreAttrType CoreAttrType, const uint8 Target)
{}
