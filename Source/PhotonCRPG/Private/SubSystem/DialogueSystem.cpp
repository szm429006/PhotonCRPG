// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/DialogueSystem.h"
#include "ArticyFlowPlayer.h"
#include "Interfaces/ArticyObjectWithText.h"
#include "Interfaces/ArticyObjectWithDisplayName.h"
#include "Interfaces/ArticyObjectWithSpeaker.h"
#include "Interfaces/ArticyNode.h"
#include "Subsystem/UISystem.h"
#include "UI/Dialogue/DialogueUI.h"
#include "Function/GlobalFunc.h"
#include "Components/ScrollBox.h"
#include "UI/Dialogue/DialogueOption.h"
#include "PhotonCRPG/ArticyGenerated/PhotoncrpggArticyTypes.h"

void UDialogueSystem::ShowDialogueItem(UArticyFlowPlayer* ArticyPlayer, const TScriptInterface<IArticyFlowObject>& PausedOn)
{
    const auto ArticyNode = Cast<UArticyNode>(PausedOn.GetObject());
    if(IsValid(ArticyNode))
    {
        EArticyPausableType NodeType = ArticyNode->GetType();
        if(NodeType == EArticyPausableType::Dialogue)
        {
            if (IsValid(ArticyPlayer))
            {
                ArticyPlayer->Play(0);
            }
        }

        if (NodeType == EArticyPausableType::DialogueFragment)
        {
            if (IsValid(ArticyPlayer))
            {
                const IArticyObjectWithSpeaker* ArticySpeaker = Cast<IArticyObjectWithSpeaker>(ArticyNode);
                const IArticyObjectWithDisplayName* ArticyDisplayName = Cast<IArticyObjectWithDisplayName>(ArticySpeaker->GetSpeaker());
                
                // 特殊处理：如果有掷骰模版，说明该选项是一个需要跳过的对话片段，直接进入掷骰后阶段
                // 这个处理是因为Articy无法配置纯选项的对话片段，把下面这段注释可看到效果
                const auto RollTemplate = Cast<UPhotoncrpggDiaRollTemplate>(ArticyNode);
                if (IsValid(RollTemplate))
                {
                    bIsSkip = true;
                }
                else
                {
                    const auto ArticyText = Cast<IArticyObjectWithText>(ArticyNode);
                    const auto DialogueUI = UGlobalFunc::GetSubsystem<UUISystem>()->LoadUI<UDialogueUI>(TEXT("/Game/Widget/WBP_DialogueUI.WBP_DialogueUI_C"));
                    if (IsValid(DialogueUI))
                    {
                        DialogueUI->AddDialogueItem(ArticyDisplayName->GetDisplayName(), ArticyText->GetText());
                    }
                    bIsSkip = false;
                }
            }
        }
    }
}

void UDialogueSystem::UpdateOptionItem(UArticyFlowPlayer* ArticyPlayer, const TArray<FArticyBranch>& AvailableBranches)
{
    const auto DialogueUI = UGlobalFunc::GetSubsystem<UUISystem>()->GetUI<UDialogueUI>();
    if (!IsValid(DialogueUI))
    {
        return;
    }

    // 特殊处理：如果上面的对话片段被挑过来了，同时跳过下面生成选项，直接执行下一个对话片段
    if (bIsSkip)
    {
        ArticyPlayer->PlayBranch(AvailableBranches[0]);
        return;
    }

    DialogueUI->GetOptionScroll()->ClearChildren();

    TArray<UDialogueOption*> Options;
    for (FArticyBranch Branch : AvailableBranches)
    {
        UDialogueOption* Option = DialogueUI->AddOptionItem(ArticyPlayer, Branch);
        if (Option->SortOrder == 0)
        {
            Options.Add(Option);
        }
        else
        {
            Options.Insert(Option, Option->SortOrder);
        }
    }

    for (const auto Option : Options)
    {
        DialogueUI->GetOptionScroll()->AddChild(Option);
    }

    if (DialogueUI->GetOptionScroll()->HasAnyChildren())
    {
        DialogueUI->GetOptionScroll()->ScrollToEnd();
    }
}

void UDialogueSystem::SetOptionInteracted(const int32 ParentId, const int32 OptionId)
{
    if (InteractedOptions.Find(ParentId) == nullptr)
    {
        const FDialogueInteractStruct DialogueData;
        InteractedOptions.Add(ParentId, DialogueData);
    }

    InteractedOptions.Find(ParentId)->OptionIds.Add(OptionId);
}

bool UDialogueSystem::IsOptionInteracted(const int32 ParentId, const int32 OptionId)
{
    const FDialogueInteractStruct* DialogueData = InteractedOptions.Find(ParentId);
    if (DialogueData == nullptr)
    {
        return false;
    }
    if (DialogueData->OptionIds.Contains(OptionId))
    {
        return true;
    }
    return false;
}
