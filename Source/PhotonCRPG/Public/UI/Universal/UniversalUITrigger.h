// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniversalUITrigger.generated.h"

class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUniversalUISignature);

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UUniversalUITrigger : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Btn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> BtnText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "按钮文字")
	FText TextContent;

public:

	FUniversalUISignature OnTriggerDelegate;

protected:

	virtual void NativePreConstruct() override;

	virtual void NativeOnInitialized() override;

public:

	virtual void SetText(const FString& InText);

protected:

	UFUNCTION()
	virtual void OnClickAction();
};
