// Fill out your copyright notice in the Description page of Project Settings.


#include "SubState/SubStateBase.h"
#include "PhotonCRPG/PhotonCRPGPlayerController.h"

void USubStateBase::StateInit(APhotonCRPGPlayerController* ControllerRef)
{
	Controller = ControllerRef;

    FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	Controller->SetInputMode(InputMode);
}

void USubStateBase::StateEnd()
{
}

bool USubStateBase::IsTriggeringDetect()
{
	return false;
}

void USubStateBase::MouseBeginClickAction()
{
}

void USubStateBase::MouseTriggeringAction()
{
}
		
// 鼠标点击结束
void USubStateBase::MouseEndClickAction()
{
}

// 鼠标点击取消
void USubStateBase::MouseCancleClickAction()
{
}
