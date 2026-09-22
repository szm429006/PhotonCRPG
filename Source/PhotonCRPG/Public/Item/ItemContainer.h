// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "ItemContainer.generated.h"

class UStaticMeshComponent;
class UItemObject;
struct FItemPack;
class USceneComponent;
class UInteractComponent;

UCLASS()
class PHOTONCRPG_API AItemContainer : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemContainer();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UInteractComponent> InteractComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="配置", DisplayName="物品包")
	TArray<FItemPack> ItemPacks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="配置", DisplayName="物品列表")
	TArray<TObjectPtr<UItemObject>> ContainedItems;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UItemObject*> GetContainedItems() const { return ContainedItems; }

	void AddItem(const int32 ItemID, const int32 Num);
	
	void RemoveAll();

	virtual void MakeInteraction() override;
};
