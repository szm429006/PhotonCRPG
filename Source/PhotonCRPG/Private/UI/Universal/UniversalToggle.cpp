// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Universal/UniversalToggle.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUniversalToggle::NativePreConstruct()
{
    Super::NativePreConstruct();
    if (!TextContent.IsEmpty())
    {
        BtnText->SetText(TextContent);
    }
}

void UUniversalToggle::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    Btn->OnClicked.AddDynamic(this, &UUniversalToggle::OnClickAction);
}

void UUniversalToggle::InitCallback(const std::function<void(UUniversalToggle*)> InCallback)
{
    Callback = InCallback;
}

void UUniversalToggle::SetText(const FString& InText)
{
    BtnText->SetText(FText::FromString(InText));
}

void UUniversalToggle::SetSelected(const bool bSelected)
{
    bIsSelected = bSelected;
    OnSelectBP();
}

// void UUniversalToggle::OnSelectBP()
// {}

void UUniversalToggle::OnClickAction()
{
    if (Callback != nullptr)
    {
        Callback(this);
    }
}