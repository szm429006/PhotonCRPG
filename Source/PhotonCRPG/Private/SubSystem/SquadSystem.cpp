// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/SquadSystem.h"
#include "Character/CharacterBase.h"
#include "Function/GlobalFunc.h"


void USquadSystem::LoadPlayer()
{
    const auto StartPoint = UGlobalFunc::GetGameMode()->FindPlayerStart(UGlobalFunc::GetController());
    const auto Player = UGlobalFunc::SpawnBPActor<ACharacterBase>(TEXT("TopDown/Character"), TEXT("BP_Player"), FTransform(StartPoint->GetActorTransform()));
    if (Player)
    {
        UGlobalFunc::GetController()->SetCurCharacter(Player);
    }
}
