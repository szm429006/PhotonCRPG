// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "Data/GameplayDataStruct.h"
#include "Data/UniversalDataStruct.h"
#include "AbilityObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityObjActivateSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityObjConfirmSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityObjCancelSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityObjEndSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityObjConsumeSignature);

class UAbilityComponent;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UAbilityObject : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TObjectPtr<UAbilityComponent> OwnerAbilityComp;

	FString ID;

	FInfoData InfoData;

	FAbilityData AbilityData;

	FGameplayAbilitySpecHandle AbilitySpecHandle;

public:

	// 能力激活委托
	FAbilityObjActivateSignature OnAbilityObjActivateDelegate;

	FAbilityObjConfirmSignature OnAbilityObjConfirmDelegate;
	
	// 能力取消委托
	FAbilityObjCancelSignature OnAbilityObjCancelDelegate;
	
	// 能力结束委托
	FAbilityObjEndSignature OnAbilityObjEndDelegate;
	
	// 能力消耗委托
	FAbilityObjConsumeSignature OnAbilityObjConsumeDelegate;

public:

	virtual void Initialize(UAbilityComponent* OwnerComp, const FString& AbilityID, const FGameplayAbilitySpecHandle& Handle,
		const luban::SharedPtr<cfg::Gameplay::AbilityTable>& AbilityTable);

	UFUNCTION(BlueprintCallable, Category = "能力系统")
	FORCEINLINE FString GetID() const { return ID; }

	UFUNCTION(BlueprintCallable, Category = "能力系统")
	FORCEINLINE FInfoData GetInfoData() const { return InfoData; }

	UFUNCTION(BlueprintCallable, Category = "能力系统")
	FORCEINLINE FAbilityData GetAbilityData() const { return AbilityData; }

	UFUNCTION(BlueprintCallable, Category = "能力系统")
	FORCEINLINE FGameplayAbilitySpecHandle GetSpecHandle() const { return AbilitySpecHandle; }
};
