// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GlobalTags.h"
#include "Engine/EngineTypes.h"

namespace GlobalTags
{
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Anim_Normal_Idle, "Anim.Normal.Idle", "常规待机");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Anim_Normal_Move, "Anim.Normal.Move", "常规移动");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Anim_Rifle_Idle, "Anim.Rifle.Idle", "持枪待机");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Anim_Rifle_Move, "Anim.Rifle.Move", "持枪移动");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Anim_Sword_Idle, "Anim.Sword.Idle", "持剑待机");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Anim_Sword_Move, "Anim.Sword.Move", "持剑移动");

    FGameplayTag FindTagByString(const FString& TagString, const bool bMatchPartialString)
    {
        const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
        FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);
        
        if (!Tag.IsValid() && bMatchPartialString)
        {
            FGameplayTagContainer AllTags;
            Manager.RequestAllGameplayTags(AllTags, true);

            for (const FGameplayTag& TestTag : AllTags)
            {
                if (TestTag.ToString().Contains(TagString))
                {
                    Tag = TestTag;
                    break;
                }
            }
        }

        return Tag;
    }

}

