// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIBase.h"
#include "SubSystem/UISystem.h"
#include "Function/GlobalFunc.h"
#include "SubSystem/GlobalEventSystem.h"
#include "Interfaces/InteractInterface.h"

void UUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BindDelegates();
}

// 绑定委托
void UUIBase::BindDelegates()
{
}

// 解绑委托
void UUIBase::UnbindDelegates()
{
}


// 加载UI
void UUIBase::DoLoad()
{
	// bIsShow = true;
	bIsClose = false;
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (CloseTimerHanlde.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(CloseTimerHanlde);
		CloseTimerDelegate.Unbind();
		CloseTimerDelegate = nullptr;
	}

	if (bIsOnlyMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIBase 加载, 仅UI操控模式"));
		// GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC) {
			FInputModeUIOnly InputMode;
			//InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());      // 可选：聚焦某 UI
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputMode);
			PC->bShowMouseCursor = true;
		}
	}
}

// 卸载UI
void UUIBase::DoUnload()
{
	// bIsShow = false;
	if (bIsOnlyMode)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
	}

	if (bIsInteractableUI)
	{
		UGlobalFunc::GetSubsystem<UGlobalEventSystem>()->BroadcastInteractFinish();
	}
}

// 关闭UI
void UUIBase::DoClose(const float CloseTime)
{
	DoUnload();
	bIsClose = true;
	SetVisibility(ESlateVisibility::Collapsed);
	CloseTimerDelegate.BindUObject(this, &UUIBase::CloseEvent);
	GetWorld()->GetTimerManager().SetTimer(CloseTimerHanlde, CloseTimerDelegate, CloseTime, false);
}

void UUIBase::CloseEvent()
{
	UnbindDelegates();
	UGlobalFunc::GetSubsystem<UUISystem>()->RemoveFromList(this);
	//GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UUISystem>()->RemoveFromList(this);
	RemoveFromParent();
}

void UUIBase::DoCloseAction()
{
	DoClose();
}
