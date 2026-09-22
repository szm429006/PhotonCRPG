// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBase.generated.h"

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UUIBase : public UUserWidget
{
	GENERATED_BODY()

private:

	// 是否显示
	// bool bIsShow;

	FTimerDelegate CloseTimerDelegate;

	FTimerHandle CloseTimerHanlde;

public:

	// 是否关闭
	bool bIsClose;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "配置", DisplayName = "排序")
	int32 ZOrder = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "配置", DisplayName = "是否仅UI操控模式")
	bool bIsOnlyMode = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "配置", DisplayName = "是否可交互UI")
	bool bIsInteractableUI = false;

protected:

	// 本地初始化
	virtual void NativeOnInitialized() override;

	// 绑定委托
	virtual void BindDelegates();

	// 解绑委托
	virtual void UnbindDelegates();

public:

	// 加载UI
	virtual void DoLoad();

	// 卸载UI
	virtual void DoUnload();

	// 关闭UI
	virtual void DoClose(const float CloseTime = 5.f);

	virtual void CloseEvent();

	UFUNCTION()
	virtual void DoCloseAction();
};
