// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotonCRPGGameState.h"
#include "Data/GlobalEnum.h"
#include "SubState/SubStateBase.h"
#include "SubState/NormalState.h"
#include "SubState/BattlePrepareState.h"
#include "Function/GlobalFunc.h"

void APhotonCRPGGameState::BeginPlay()
{
    Super::BeginPlay();
    SetGameStateType(EGameStateType::Normal);
}

void APhotonCRPGGameState::SetGameStateType(const EGameStateType Type)
{
    if (CurSubState != nullptr)
    {
        CurSubState->StateEnd();
    }

    CurGameStateType = Type;
    switch (CurGameStateType)
    {
        case EGameStateType::Normal:
        case EGameStateType::Scenario:
        case EGameStateType::PlayerBattle:
        case EGameStateType::AIBattle:
        case EGameStateType::BattleEnd:
            CurSubState = NewObject<UNormalState>(this);
            break;

        case EGameStateType::BattlePrepare:
            CurSubState = NewObject<UBattlePrepareState>(this);
            break;
    }

    // 初始化新状态
    CurSubState->StateInit(UGlobalFunc::GetController());
}
