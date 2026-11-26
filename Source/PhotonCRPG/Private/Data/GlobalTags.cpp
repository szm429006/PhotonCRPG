// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GlobalTags.h"
#include "Engine/EngineTypes.h"

namespace GlobalTags
{
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability, "Ability", "通用能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Move, "Ability.Move", "移动能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Move_AI, "Ability.Move.AI", "AI移动能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Death, "Ability.Death", "死亡能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_HHitReaction, "Ability.HitReaction", "受击反应能力");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Shoot_Pistol, "Ability.Shoot.Pistol", "手枪射击能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Shoot_Rifle, "Ability.Shoot.Rifle", "步枪射击能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Shoot_Sniper, "Ability.Shoot.Sniper", "狙击枪射击能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Reload, "Ability.Reload", "换弹能力");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Sword_Skill1, "Ability.Sword.Skill1", "剑技能1");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Sword_Skill2, "Ability.Sword.Skill2", "剑技能2");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Cost_AP, "Cost.AP", "消耗行动点");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Cost_MP, "Cost.MP", "消耗移动点");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Select_Confirm, "Select.Confirm", "确认选择");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Select_Cancel, "Select.Cancel", "取消选择");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Cast, "Event.Cast", "释放事件");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Hit, "Event.Hit", "命中事件");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Data_Damage, "Data.Damage", "伤害数据");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Data_Heal, "Data.Heal", "治疗数据");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Dead, "State.Dead", "死亡状态");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(Execution_ShowDamage, "Execution.ShowDamage", "执行 - 显示伤害");

    UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayCue_DamageText, "GameplayCue.DamageText", "伤害跳字");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayCue_HealText, "GameplayCue.HealText", "治疗跳字");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayCue_IsHit, "GameplayCue.IsHit", "是否命中");
    UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayCue_IsCritical, "GameplayCue.IsCritical", "是否暴击");

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

