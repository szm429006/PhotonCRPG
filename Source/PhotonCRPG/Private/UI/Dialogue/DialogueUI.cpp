// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Dialogue/DialogueUI.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "UI/Dialogue/DialogueItem.h"
#include "UI/Dialogue/DialogueOption.h"
#include "ArticyFlowPlayer.h"
#include "Interfaces/ArticyObjectWithMenuText.h"
#include "Interfaces/ArticyObjectWithDisplayName.h"
#include "Interfaces/ArticyObjectWithSpeaker.h"
#include "Interfaces/ArticyNode.h"
#include "Subsystem/DialogueSystem.h"
#include "Subsystem/UISystem.h"
#include "Function/GlobalFunc.h"

void UDialogueUI::DoLoad()
{
    Super::DoLoad();
}

void UDialogueUI::DoUnload()
{
    Super::DoUnload();
}

void UDialogueUI::DoClose(const float CloseTime)
{
    ContentScroll->ClearChildren();
    OptionScroll->ClearChildren();

    UGlobalFunc::GetGameMode()->ArticyEndDialogue();
    Super::DoClose(CloseTime);
}

void UDialogueUI::AddDialogueItem(const FText& Name, const FText& Content)
{
    SpeakerName->SetText(Name);

    const auto DialogueItem = CreateWidget<UDialogueItem>(this, UDialogueItemClass);
    ContentScroll->AddChild(DialogueItem);
    DialogueItem->RefreshData(Content);

    ContentScroll->ScrollToEnd();

    if (ContentScroll->GetChildrenCount() > 1)
    {
        const auto LastDialogueItem = Cast<UDialogueItem>(ContentScroll->GetChildAt(ContentScroll->GetChildrenCount() - 1));
        LastDialogueItem->SetIsRead();
    }
}

UDialogueOption* UDialogueUI::AddOptionItem(UArticyFlowPlayer* ArticyPlayer, const FArticyBranch& Branch)
{
    const auto OptionItem = CreateWidget<UDialogueOption>(this, UDialogueOptionClass);
    OptionItem->RefreshData(ArticyPlayer, Branch);
    return OptionItem;
}
