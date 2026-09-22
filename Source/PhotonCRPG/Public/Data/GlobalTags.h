// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GlobalTags
{
	PHOTONCRPG_API FGameplayTag FindTagByString(const FString& TagString, const bool bMatchPartialString = false);

	PHOTONCRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Anim_Normal_Idle);
	PHOTONCRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Anim_Normal_Move);

	PHOTONCRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Anim_Rifle_Idle);
	PHOTONCRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Anim_Rifle_Move);

	PHOTONCRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Anim_Sword_Idle);
	PHOTONCRPG_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Anim_Sword_Move);
}
