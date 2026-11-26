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
#include "Subsystem/DiceSystem.h"
#include "PhotonCRPG/ArticyGenerated/PhotoncrpggArticyTypes.h"

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

    DiceContent->SetVisibility(ESlateVisibility::Collapsed);
    bIsContinue = false;
    bIsClose = false;

    if (IsValid(BaseObject))
    {
        ParentId = BaseObject->GetParentID();
        OptionId = BaseObject->GetId();
        bIsInteracted = UGlobalFunc::GetSubsystem<UDialogueSystem>()->IsOptionInteracted(ParentId, OptionId);

        RollTemplate = Cast<UPhotoncrpggDiaRollTemplate>(Branch.GetTarget().GetObject());

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

                // 如果有掷骰信息，显示在骰子内容中
                if (IsValid(RollTemplate))
                {
                    const auto RollData = RollTemplate->GetFeatureRollData();
                    const ECoreAttrType AttrType = static_cast<ECoreAttrType>(RollData->AttrType);
                    const uint8 AttrLevel = UGlobalFunc::GetPlayerCoreAttrLevel(AttrType);
                    const uint8 RollTarget = static_cast<uint8>(RollData->RollTarget);
                    const float PassRate = UGlobalFunc::GetSubsystem<UDiceSystem>()->GetPassRate_2D6(AttrType, RollTarget) * 100;

                    FNumberFormattingOptions Options;
                    Options.MinimumFractionalDigits = 1;
                    Options.MaximumFractionalDigits = 2;
                    const FText DiceTextContent = FText::Format(NSLOCTEXT("Common", "Roll", "{0}({1})，目标：{2}点，{3}%"),
                        FText::FromString(UGlobalFunc::GetLocNameByEnum(AttrType)), AttrLevel, RollTarget, FText::AsNumber(PassRate, &Options));
                    DiceContent->SetText(DiceTextContent);
                    DiceContent->SetVisibility(ESlateVisibility::Visible);
                }
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
        // 如果选项有掷骰要求，先进行掷骰
        if (IsValid(RollTemplate))
        {
            const auto RollData = RollTemplate->GetFeatureRollData();
            const ECoreAttrType AttrType = static_cast<ECoreAttrType>(RollData->AttrType);
            if (UGlobalFunc::GetSubsystem<UDiceSystem>()->GetCheckResult(AttrType, RollData->RollTarget))
            {
                RollData->PassResult->Execute();
            }
        }
        else
        {
            if (!bIsContinue)
            {
                UGlobalFunc::GetSubsystem<UDialogueSystem>()->SetOptionInteracted(ParentId, OptionId);
            }
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
