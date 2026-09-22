// Fill out your copyright notice in the Description page of Project Settings.


#include "SubState/BattlePrepareState.h"
#include "UI/GameUI.h"
#include "SubSystem/UISystem.h"
#include "Function/GlobalFunc.h"
#include "PhotonCRPG/PhotonCRPGPlayerController.h"

void UBattlePrepareState::StateInit(APhotonCRPGPlayerController* ControllerRef)
{
    Super::StateInit(ControllerRef);

    UGlobalFunc::GetSubsystem<UUISystem>()->GetUI<UGameUI>()->ShowStartBtn(true);
}

void UBattlePrepareState::StateEnd()
{
    Super::StateEnd();

    UGlobalFunc::GetSubsystem<UUISystem>()->GetUI<UGameUI>()->ShowStartBtn(false);
}
