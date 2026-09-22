// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/AttributeHandlerComponent.h"
#include "Character/CharacterBase.h"
#include "GAS/Attribute/BasicAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemInterface.h"
#include "Character/Components/AbilityComponent.h"

// Sets default values for this component's properties
UAttributeHandlerComponent::UAttributeHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributeHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributeHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttributeHandlerComponent::DoInitialize()
{
	Owner = Cast<ACharacterBase>(GetOwner());
	BindAttributeDelegates();
	UE_LOG(LogTemp, Warning, TEXT("AttributeHandlerComponent DoInitialize Finished..."));
}

void UAttributeHandlerComponent::DoReset()
{
	IUnitComponentInterface::DoReset();
}

void UAttributeHandlerComponent::DoDispose()
{
	ClearAttributeDelegates();
}

ACharacterBase* UAttributeHandlerComponent::GetCompOwner() const
{
	return Owner;
}

void UAttributeHandlerComponent::BindAttributeDelegates()
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([&]()
	{
		Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetHealthAttribute()).AddUObject(this, &UAttributeHandlerComponent::OnBasicAttributeChanged);
		Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetArmorAttribute()).AddUObject(this, &UAttributeHandlerComponent::OnBasicAttributeChanged);
		Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetAPAttribute()).AddUObject(this, &UAttributeHandlerComponent::OnBasicAttributeChanged);
		Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetMPAttribute()).AddUObject(this, &UAttributeHandlerComponent::OnBasicAttributeChanged);
	});
}

void UAttributeHandlerComponent::ClearAttributeDelegates()
{
	Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetHealthAttribute()).Clear();
	Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetArmorAttribute()).Clear();
	Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetAPAttribute()).Clear();
	Owner->GetAbilityComp()->GetGameplayAttributeValueChangeDelegate(UBasicAttributeSet::GetMPAttribute()).Clear();
}

void UAttributeHandlerComponent::OnBasicAttributeChanged(const FOnAttributeChangeData& Data)
{
	// 基础信息
	const FGameplayAttribute& ChangedAttribute = Data.Attribute;
	float OldValue = Data.OldValue;
	float NewValue = Data.NewValue;

	// 获取来源信息
	if (Data.GEModData)
	{
		const FGameplayEffectSpec& EffectSpec = Data.GEModData->EffectSpec;

		AActor* SourceActor = nullptr;
		if (Data.GEModData->EffectSpec.GetContext().GetEffectCauser())
		{
			SourceActor = Data.GEModData->EffectSpec.GetContext().GetEffectCauser();
		}
	}

	if (ChangedAttribute == UBasicAttributeSet::GetHealthAttribute())
	{
		// 生命值
	}

	if (ChangedAttribute == UBasicAttributeSet::GetArmorAttribute())
	{
		// 护甲值
	}

	if (OnAttributeChangedDelegate.IsBound())
	{
		OnAttributeChangedDelegate.Broadcast();
	}
}
