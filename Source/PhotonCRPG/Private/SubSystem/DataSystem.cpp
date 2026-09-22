// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DataSystem.h"
#include "PhotonCRPG/Luban/ByteBuf.h"



void UDataSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const std::string Path = UDataFunc::FStringToStd(FPaths::ProjectContentDir());
    if (GlobalTables.load([&](::luban::ByteBuf& buf, const std::string& s) { return buf.loadFromFile(Path + "Data/LubanGenerated/" + s + ".bytes"); }))
    {
        UE_LOG(LogTemp, Warning, TEXT("== 数据表加载成功 =="));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("== 数据表加载失败 =="));
    }
}
