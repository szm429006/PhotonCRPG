// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/GlobalEnum.h"
#include "Data/CharacterDataStruct.h"
#include "Data/UniversalDataStruct.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Interfaces/InteractInterface.h"
#include "Data/GlobalTags.h"
#include "Character/Components/AbilityComponent.h"
#include "CharacterBase.generated.h"

class UCapsuleComponent;
class UCharacterMovementComponent;
class UAttributeHandlerComponent;
class UBasicAttributeSet;
class UAbilitySystemComponent;
class UAbilityComponent;
class UCoreAttributeSet;
class UBattleAttributeSet;
class UEquipComponent;
class UAttributeSetBase;
struct FGearData;
class UStaticMeshComponent;
struct FGameplayTag;
class UWeaponObject;
class UInteractComponent;

UCLASS()
class PHOTONCRPG_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:

	UPROPERTY()
	TObjectPtr<UBasicAttributeSet> BasicAttrSet;

	UPROPERTY()
	TObjectPtr<UCoreAttributeSet> CoreAttrSet;

	UPROPERTY()
	TObjectPtr<UBattleAttributeSet> BattleAttrSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "组件", DisplayName = "能力组件")
	TObjectPtr<UAbilityComponent> AbilityComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "组件", DisplayName = "属性组件")
	TObjectPtr<UAttributeHandlerComponent> AttrHandlerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "组件", DisplayName = "装备组件")
	TObjectPtr<UEquipComponent> EquipComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UInteractComponent> InteractComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "配置", DisplayName = "角色ID")
	FString CharacterID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "数据", DisplayName = "角色信息")
	FCharInfoData CharInfoData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "数据", DisplayName = "阵营")
	EFactionType Faction = EFactionType::NPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "数据", DisplayName = "对话ID")
	int32 ArticyID = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "数据", DisplayName = "动画标签")
	FGameplayTag AnimTag;

	UPROPERTY()
	TArray<TObjectPtr<UAttributeSetBase>> OwnedAttributeSets;

private:

	UPROPERTY()
	TArray<TObjectPtr<UStaticMeshComponent>> LoadedWeapons;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeData();

	// 死亡回调
	void OnDeathStateChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UFUNCTION(BlueprintCallable)
	void AnimTest(const bool bIsInBattle);

	void SetAnimTag(const bool bIsInBattle);

	void LoadWeapon();

	void RemoveWeapon();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// 更换装备
	void GearChange(const FGearData& InGear, const bool bIsWear = true);

	virtual void MakeInteraction() override;

	UFUNCTION(BlueprintCallable, Category = "角色")
	FORCEINLINE FString GetCharacterID() const { return CharacterID; }

	UFUNCTION(BlueprintCallable, Category = "角色")
	FORCEINLINE EFactionType GetFaction() const { return Faction; }

	UFUNCTION(BlueprintCallable, Category = "角色")
	FORCEINLINE FCharInfoData GetInfo() const { return CharInfoData; }

	UFUNCTION(BlueprintCallable, Category = "角色")
	FORCEINLINE UAbilityComponent* GetAbilityComp() const { return AbilityComp; }

	UFUNCTION(BlueprintCallable, Category = "角色")
	FORCEINLINE UAttributeHandlerComponent* GetAttrHandlerComp() const { return AttrHandlerComp; }

	UFUNCTION(BlueprintCallable, Category = "角色")
	FORCEINLINE UEquipComponent* GetEquipComp() const { return EquipComp; }

	UFUNCTION(BlueprintCallable, Category = "角色")
	FORCEINLINE bool IsDead() const { return AbilityComp->HasMatchingGameplayTag(GlobalTags::State_Dead); }
};
