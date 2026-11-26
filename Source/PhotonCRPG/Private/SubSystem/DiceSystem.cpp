// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DiceSystem.h"
#include "Function/GlobalFunc.h"
#include "Subsystems/SubsystemCollection.h"

void UDiceSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    TMap<uint8, uint8> ResultMatrix_2D6;

    UE_LOG(LogTemp, Warning, TEXT("初始化掷骰子通过率"));

	// 初始化掷骰子通过率
	for (uint8 i = 1; i <= 6; i++)
	{
		for (uint8 j = 1; j <= 6; j++)
		{
			const uint8 Value = i + j;
            if (!ResultMatrix_2D6.Contains(Value))
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
    const uint8 AttrLevel = UGlobalFunc::GetPlayerCoreAttrLevel(CoreAttrType);
    if (AttrLevel == -1)
        return 0.f;

    float PassRate = 0.f;
    for (const auto Probability : ProbabilityMap_2D6)
    {
        if (Probability.Key >= Target - AttrLevel)
        {
            PassRate += Probability.Value;
        }
    }
    return PassRate;
}

bool UDiceSystem::GetCheckResult(const ECoreAttrType CoreAttrType, const uint8 Target)
{
    uint8 RollResult = 0;

    for (uint8 i = 0; i < 2; i++)
    {
        const uint8 Roll = FMath::RandRange(1, 6);
        RollResult += Roll;
    }

    const uint8 AttrLevel = UGlobalFunc::GetPlayerCoreAttrLevel(CoreAttrType);
    if (AttrLevel == -1)
        return false;
    
    const bool bIsPass = RollResult + AttrLevel >= Target;

    UE_LOG(LogTemp, Warning, TEXT("掷骰子结果: %d, 属性等级: %d, 是否通过: %s"), RollResult, AttrLevel, bIsPass ? TEXT("是") : TEXT("否"));

    return bIsPass;
}
