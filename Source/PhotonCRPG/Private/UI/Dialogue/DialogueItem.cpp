// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Dialogue/DialogueItem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDialogueItem::RefreshData(const FText& Content) const
{
    TextContent->SetText(Content);
}

void UDialogueItem::SetIsRead()
{
    OnReadBP();
}
