// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Universal/UniversalUITrigger.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUniversalUITrigger::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (!TextContent.IsEmpty())
    {
        BtnText->SetText(TextContent);
    }
}

void UUniversalUITrigger::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    Btn->OnClicked.AddDynamic(this, &UUniversalUITrigger::OnClickAction);
}

void UUniversalUITrigger::SetText(const FString& InText)
{
    if (!InText.IsEmpty())
    {
        BtnText->SetText(FText::FromString(InText));
    }
}

void UUniversalUITrigger::OnClickAction()
{
    if (OnTriggerDelegate.IsBound())
    {
        OnTriggerDelegate.Broadcast();
    }
}

