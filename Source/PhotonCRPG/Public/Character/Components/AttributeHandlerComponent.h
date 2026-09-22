// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/UnitComponentInterface.h"
#include "AttributeHandlerComponent.generated.h"

class ACharacterBase;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributeChangedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOTONCRPG_API UAttributeHandlerComponent : public UActorComponent, public IUnitComponentInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeHandlerComponent();

public:

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedSignature OnAttributeChangedDelegate;

protected:

	UPROPERTY()
	TObjectPtr<ACharacterBase> Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void DoInitialize() override;

	virtual void DoReset() override;
	
	virtual void DoDispose() override;
	
	virtual ACharacterBase* GetCompOwner() const override;

protected:

	void BindAttributeDelegates();

	void ClearAttributeDelegates();

	void OnBasicAttributeChanged(const FOnAttributeChangeData& Data);
};
