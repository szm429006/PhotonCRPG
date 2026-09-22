// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SubSystem/DataSystem.h"
#include "Function/GlobalFunc.h"
#include "Interfaces/UnitComponentInterface.h"
#include "Character/Components/AttributeHandlerComponent.h"
#include "GAS/Attribute/BasicAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Character/Components/AbilityComponent.h"
#include "Character/Components/EquipComponent.h"
#include "GAS/Attribute/CoreAttributeSet.h"
#include "GAS/Attribute/BattleAttributeSet.h"
#include "GAS/Attribute/AttributeSetBase.h"
#include "Data/GlobalEnum.h"
#include "Data/CharacterDataStruct.h"
#include "Data/ItemDataStruct.h"
#include "Function/DataFunc.h"
#include "Data/GlobalTags.h"
#include "Components/StaticMeshComponent.h"
#include "Item/WeaponObject.h"

// Sets default values
ACharacterBase::ACharacterBase()
{

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Auto possess AI
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("CreateDefaultSubobject<UBasicAttributeSet>(TEXT(\"BasicAttrSet\"))"));
	BasicAttrSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttrSet"));

	UE_LOG(LogTemp, Warning, TEXT("CreateDefaultSubobject<UCoreAttributeSet>(TEXT(\"CoreAttrSet\"))"));
	CoreAttrSet = CreateDefaultSubobject<UCoreAttributeSet>(TEXT("CoreAttrSet"));

	UE_LOG(LogTemp, Warning, TEXT("CreateDefaultSubobject<UBattleAttributeSet>(TEXT(\"BattleAttrSet\"))"));
	BattleAttrSet = CreateDefaultSubobject<UBattleAttributeSet>(TEXT("BattleAttrSet"));

	// Create ability component
	AbilityComp = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComp"));

	// Create attribute handler component
	AttrHandlerComp = CreateDefaultSubobject<UAttributeHandlerComponent>(TEXT("AttrHandlerComp"));

	// Create equip component
	UE_LOG(LogTemp, Warning, TEXT("CreateDefaultSubobject<UEquipComponent>(TEXT(\"EquipComp\"))"));
	EquipComp = CreateDefaultSubobject<UEquipComponent>(TEXT("EquipComp"));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeData();
}

void ACharacterBase::InitializeData_Implementation()
{
	const auto TbCharacterData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbCharacterData(CharacterID);
	if (TbCharacterData != nullptr)
	{
		CharInfoData = FCharInfoData(TbCharacterData);
		Faction = static_cast<EFactionType>(TbCharacterData->faction);
	}

	// UE_LOG(LogTemp, Warning, TEXT("InitializeData_Implementation: TbCharacterData"));

	const auto SpawnedAttributes = GetAbilityComp()->GetSpawnedAttributes();
	if (SpawnedAttributes.Num() > 0)
	{
		// 	初始化组件
		for (UAttributeSet* AttributeSet : SpawnedAttributes)
		{
			// UE_LOG(LogTemp, Warning, TEXT("InitializeData_Implementation: AttributeSet"));
			const auto AttrSet = Cast<UAttributeSetBase>(AttributeSet);
			if (AttrSet != nullptr)
			{
				// UE_LOG(LogTemp, Warning, TEXT("InitializeData_Implementation: OwnedAttributeSets"));
				OwnedAttributeSets.AddUnique(AttrSet);
				AttrSet->DoInitialize();
			}
		}
	}
	

	// UE_LOG(LogTemp, Warning, TEXT("InitializeData_Implementation: UnitComps"));

	// 初始化身上所有插件
	const auto UnitComps = GetComponentsByInterface(UUnitComponentInterface::StaticClass());
	if (UnitComps.Num() > 0)
	{
		// UE_LOG(LogTemp, Warning, TEXT("InitializeData_Implementation: UnitComps.Num() > 0"));

		for (const auto& Comp : UnitComps)
		{
			if (Comp != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("InitializeData_Implementation: %s"), *Comp->GetName());
				Cast<IUnitComponentInterface>(Comp)->DoInitialize();
			}
		}
	}
}

void ACharacterBase::AnimTest(const bool bIsInBattle)
{
	if (bIsInBattle)
	{
		SetAnimTag(true);
		LoadWeapon();
	}
	else
	{
		SetAnimTag(false);
		RemoveWeapon();
	}
} 

void ACharacterBase::SetAnimTag(const bool bIsInBattle)
{
	if (bIsInBattle && IsValid(EquipComp->GetWeapons().FindRef(0)))
	{
		AnimTag = GlobalTags::FindTagByString(EquipComp->GetWeapons().FindRef(0)->GetGearData().IdleAnimTag, true);
	}
	else
	{
		AnimTag = GlobalTags::Anim_Normal_Idle;
	}
}

void ACharacterBase::LoadWeapon()
{
	bool bIsDoubleHandAdded = false;

	const auto Weapons = EquipComp->GetWeapons();
	for (const auto Weapon : Weapons)
	{
		if (bIsDoubleHandAdded)
			break;
		
		const auto WeaponMesh = LoadObject<UStaticMesh>(nullptr, *Weapon.Value->GetGearData().Model);
		if (IsValid(WeaponMesh))
		{
			const auto WeaponMeshComp = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
			if (IsValid(WeaponMeshComp))
			{
				WeaponMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
					*Weapon.Value->GetGearData().Socket);
				WeaponMeshComp->RegisterComponent();
				WeaponMeshComp->SetStaticMesh(WeaponMesh);
				LoadedWeapons.Add(WeaponMeshComp);
			}

			if (Weapon.Value->IsTwoHand())
			{
				bIsDoubleHandAdded = true;
			}
		}
	}
}

void ACharacterBase::RemoveWeapon()
{
	for (const auto Weapon : LoadedWeapons)
	{
		Weapon->DestroyComponent();
	}
	LoadedWeapons.Empty();
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilityComp;
}

void ACharacterBase::GearChange(const FGearData& InGear, const bool bIsWear)
{
	for (auto AttrSet : OwnedAttributeSets)
	{
		AttrSet->GearChange(InGear, bIsWear);
	}
}
