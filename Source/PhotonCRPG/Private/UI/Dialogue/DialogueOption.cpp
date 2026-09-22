// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Dialogue/DialogueOption.h"
#include "UI/Dialogue/DialogueUI.h"
#include "Subsystem/DialogueSystem.h"
#include "Subsystem/UISystem.h"
#include "ArticyObject.h"
#include "Interfaces/ArticyObjectWithMenuText.h"
#include "Interfaces/ArticyObjectWithDisplayName.h"
#include "Interfaces/ArticyObjectWithSpeaker.h"
#include "Interfaces/ArticyNode.h"
#include "ArticyFlowPlayer.h"
#include "Function/GlobalFunc.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDialogueOption::NativeConstruct()
{
    Super::NativeConstruct();
    Btn->OnClicked.AddDynamic(this, &UDialogueOption::OnClickAction);
}

void UDialogueOption::RefreshData(UArticyFlowPlayer* ArticyPlayer, const FArticyBranch& Branch)
{
    DialoguePlayer = ArticyPlayer;
    DialogueBranch = Branch;

    const auto BaseObject = Cast<UArticyObject>(Branch.GetTarget().GetObject());
    bIsContinue = false;
    bIsClose = false;

    if (IsValid(BaseObject))
    {
        ParentId = BaseObject->GetParentID();
        OptionId = BaseObject->GetId();
        bIsInteracted = UGlobalFunc::GetSubsystem<UDialogueSystem>()->IsOptionInteracted(ParentId, OptionId);

        IArticyObjectWithMenuText* ArticyMenuText = Cast<IArticyObjectWithMenuText>(Branch.GetTarget().GetObject());
        if (ArticyMenuText)
        {
            FText Content = ArticyMenuText->GetMenuText();
            if (Content.IsEmpty())
            {
                bIsContinue = true;
                TextContent->SetText(NSLOCTEXT("Common", "Continue", "继续"));
            }
            else
            {
                TextContent->SetText(Content);
            }
        }
    }
    else
    {
        bIsClose = true;
        TextContent->SetText(NSLOCTEXT("Common", "End", "结束"));
    }
}

void UDialogueOption::OnClickAction()
{
    if (!bIsClose)
    {
        if (!bIsContinue)
        {
            UGlobalFunc::GetSubsystem<UDialogueSystem>()->SetOptionInteracted(ParentId, OptionId);
        }

        if (IsValid(DialoguePlayer))
        {
            DialoguePlayer->PlayBranch(DialogueBranch);
        }
    }
    else
    {
        UGlobalFunc::GetSubsystem<UUISystem>()->CloseUI<UDialogueUI>();
    }
}
