// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SubStateBase.generated.h"

class APhotonCRPGPlayerController;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API USubStateBase : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TObjectPtr<APhotonCRPGPlayerController> Controller;

public:

	// 初始化
	virtual void StateInit(APhotonCRPGPlayerController* ControllerRef);

	// 结束
	virtual void StateEnd();

	// 是否检测按住鼠标
	virtual bool IsTriggeringDetect();

	// 鼠标点击开始
	virtual void MouseBeginClickAction();

	virtual void MouseTriggeringAction();
		
	// 鼠标点击结束
	virtual void MouseEndClickAction();

	// 鼠标点击取消
	virtual void MouseCancleClickAction();
};
