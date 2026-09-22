// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "InteractComponent.generated.h"

class UUniversalUITrigger;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UInteractComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "配置", DisplayName = "交互组件")
	TObjectPtr<UWidgetComponent> InteractWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "配置", DisplayName = "交互按钮文本")
	FString InteractBtnText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "配置", DisplayName = "是否启用交互按钮")
	bool bInteractEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "配置", DisplayName = "是否允许重复交互")
	bool bCanRepeat = true;

	UPROPERTY()
	TObjectPtr<UUniversalUITrigger> Trigger;

private:

	bool bInteracting = false;

	uint8 InTriggerActorCount = 0;

public:

	virtual void OnRegister() override;

	virtual void BeginPlay() override;

protected:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	void OnInteractFinish();

public:

	UFUNCTION()
	void MakeInteraction();

	UFUNCTION()
	FORCEINLINE void SetCanInteract(const bool bEnabled) { bInteractEnabled = bEnabled; }
};
