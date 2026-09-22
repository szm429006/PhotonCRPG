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
                const auto ArticyText = Cast<IArticyObjectWithText>(ArticyNode);

                const auto DialogueUI = UGlobalFunc::GetSubsystem<UUISystem>()->LoadUI<UDialogueUI>();
                if (IsValid(DialogueUI))
                {
                    DialogueUI->AddDialogueItem(ArticyDisplayName->GetDisplayName(), ArticyText->GetText());
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
