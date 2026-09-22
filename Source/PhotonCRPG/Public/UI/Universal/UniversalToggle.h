// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include "Blueprint/UserWidget.h"
#include "UniversalToggle.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UUniversalToggle : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BtnText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "按钮文字")
	FText TextContent;

	// 回调
	std::function<void(UUniversalToggle*)> Callback;

public:

	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected;

protected:

	virtual void NativePreConstruct() override;

	virtual void NativeOnInitialized() override;

public:

	virtual void InitCallback(const std::function<void(UUniversalToggle*)> InCallback = nullptr);

	virtual void SetText(const FString& InText);

	void SetSelected(const bool bSelected);

protected:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnSelectBP();

	UFUNCTION()
	virtual void OnClickAction();
};
