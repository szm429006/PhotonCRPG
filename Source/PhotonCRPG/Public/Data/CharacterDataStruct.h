// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/UniversalDataStruct.h"
#include "SubSystem/DataSystem.h"
#include "Function/DataFunc.h"
#include "CharacterDataStruct.generated.h"

/**
 * 
 */
class PHOTONCRPG_API CharacterDataStruct
{
public:
	CharacterDataStruct();
	~CharacterDataStruct();
};

USTRUCT(BlueprintType)
struct FCharInfoData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色 | 角色信息", DisplayName = "通用信息")
	FInfoData InfoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色 | 角色信息", DisplayName = "年龄")
	int32 Age;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色 | 角色信息", DisplayName = "背景故事")
	FString Story;

	FCharInfoData()
		: Age(0)
		, Story("")
	{}

	explicit FCharInfoData(const luban::SharedPtr<cfg::Character::CharacterTable>& TableData)
		: InfoData(FInfoData(TableData->basicInfo))
		, Age(TableData->age)
		, Story(UDataFunc::StdToFString(TableData->story))
	{}
};