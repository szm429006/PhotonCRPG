// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/InteractComponent.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/GlobalEventSystem.h"
#include "Interfaces/InteractInterface.h"
#include "UI/Universal/UniversalUITrigger.h"
#include "Components/WidgetComponent.h"

UInteractComponent::UInteractComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
}

void UInteractComponent::OnRegister()
{
    Super::OnRegister();

    if (InteractWidget && GetOwner())
    {
        if (!InteractWidget->IsRegistered())
        {
            InteractWidget->RegisterComponent();
        }

        if (USceneComponent* RootComp = GetOwner()->GetRootComponent())
        {
            InteractWidget->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
        }
    }
}

void UInteractComponent::BeginPlay()
{
    Super::BeginPlay();

    InteractWidget->InitWidget();
    const auto Widget = InteractWidget->GetWidget();
    if (IsValid(Widget) && Widget->IsA(UUniversalUITrigger::StaticClass()))
    {
        Trigger = Cast<UUniversalUITrigger>(Widget);
        Trigger->SetText(InteractBtnText);
        Trigger->OnTriggerDelegate.AddDynamic(this, &UInteractComponent::MakeInteraction);
        Trigger->SetVisibility(ESlateVisibility::Collapsed);
    }

    this->OnComponentBeginOverlap.AddDynamic(this, &UInteractComponent::OnOverlapBegin);
    this->OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnOverlapEnd);

    UGlobalFunc::GetSubsystem<UGlobalEventSystem>()->OnInteractFinishDelegate.AddDynamic(this, &UInteractComponent::OnInteractFinish);
}

void UInteractComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bInteractEnabled)
    {
        return;
    }

    if (IsValid(OtherActor) && OtherActor == UGlobalFunc::GetController()->GetCurCharacter())
    {
        Trigger->SetVisibility(ESlateVisibility::Visible);
        InTriggerActorCount++;
    }
}

void UInteractComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex)
{
    if (!bInteractEnabled)
    {
        return;
    }

    if (IsValid(OtherActor) && OtherActor == UGlobalFunc::GetController()->GetCurCharacter())
    {
        InTriggerActorCount--;
        if (InTriggerActorCount <= 0)
        {
            Trigger->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void UInteractComponent::OnInteractFinish()
{
    if (!bInteractEnabled)
    {
        return;
    }
    bInteracting = false;

    if (bCanRepeat && InTriggerActorCount > 0)
    {
        Trigger->SetVisibility(ESlateVisibility::Visible);
    }
}

void UInteractComponent::MakeInteraction()
{
    if (IInteractInterface* OwnerInterface = Cast<IInteractInterface>(GetOwner()); OwnerInterface != nullptr)
    {
        OwnerInterface->MakeInteraction();
        UGlobalFunc::GetController()->GetCurCharacter()->GetController()->StopMovement();
        Trigger->SetVisibility(ESlateVisibility::Collapsed);
        bInteracting = true;
    }
}
