// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/UIBase.h"
#include "UISystem.generated.h"

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UUISystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UUISystem();

protected:

	UPROPERTY()
	TArray<TObjectPtr<UUIBase>> UIList;

public:

	// 
	template<typename WidgetT = UUIBase>
	WidgetT* LoadUI(const FString& Path)
	{
		// 获取UI名称
		const FString WidgetName = WidgetT::StaticClass()->GetName();
		if (WidgetT* InListUI = GetUI<WidgetT>(); IsValid(InListUI))
		{
			// 如果UI已关闭，加载UI
			if (InListUI->bIsClose)
			{
				// 加载UI
				InListUI->DoLoad();
			}
			return InListUI;
		}
		// const FString Path = FString::Printf(TEXT("/Game/Widget/WBP_%s.WBP_%s_C"), *WidgetName, *WidgetName);
		// 加载UI
		UClass* WidgetClass = LoadClass<UUIBase>(nullptr, *Path);

		if (WidgetClass)
		{
			if (WidgetT* UI = Cast<WidgetT>(CreateWidget<UUserWidget>(GetWorld(), WidgetClass)))
			{
				UI->AddToViewport(UI->ZOrder);
				UI->DoLoad();
				UIList.Add(UI);
				return UI;
			}
			return nullptr;
		}
		return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UUIBase* LoadUI(const TSubclassOf<UUIBase> WidgetClass)
	{
		if (UUIBase* InListUI = GetUI(WidgetClass); IsValid(InListUI))
		{
			if (InListUI->bIsClose)
			{
				InListUI->DoLoad();
			}
			return InListUI;
		}

		if (WidgetClass)
		{
			UUIBase* UI = Cast<UUIBase>(CreateWidget<UUserWidget>(GetWorld(), WidgetClass));
			UI->AddToViewport(UI->ZOrder);
			UI->DoLoad();
			UIList.Add(UI);
			return UI;
		}

		return nullptr;
	}

	// 获取UI
	template<typename WidgetT = UUIBase>
	WidgetT* GetUI()
	{
		UClass* ParentClass = GetParentNativeClass(WidgetT::StaticClass());
		const TObjectPtr<UUIBase>* FoundUIClass = UIList.FindByPredicate([ParentClass](const UUIBase* UIClass)
		{
				return GetParentNativeClass(UIClass->GetClass()) == ParentClass;
		});

		if (FoundUIClass)
		{
			WidgetT* UI = Cast<WidgetT>(*FoundUIClass);
			return UI;
		}
		return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UUIBase* GetUI(const TSubclassOf<UUIBase> Class)
	{
		UClass* ParentClass = GetParentNativeClass(Class.Get());
		const TObjectPtr<UUIBase>* FoundUIClass = UIList.FindByPredicate([ParentClass](const UUIBase* UIClass)
			{
				return GetParentNativeClass(UIClass->GetClass()) == ParentClass;
			});

		if (FoundUIClass)
		{
			UUIBase* UI = Cast<UUIBase>(*FoundUIClass);
			return UI;
		}
		return nullptr;
	}

	// 关闭UI
	template<typename WidgetT = UUIBase>
	void CloseUI()
	{
		if (WidgetT* UI = GetUI<WidgetT>(); IsValid(UI))
		{
			if (!UI->bIsClose)
			{
				UI->DoClose();
			}
		}
	}

	// 关闭UI
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void CloseUI(const TSubclassOf<UUIBase> WidgetClass)
	{
		if (UUIBase* UI = GetUI(WidgetClass); IsValid(UI))
		{
			if (!UI->bIsClose)
			{
				UI->DoClose();
			}
		}
	}

	// 切换UI显示状态
	template<typename WidgetT = UUIBase>
	void ToggleUI(const FString& Path)
	{
		if (WidgetT* UI = GetUI<WidgetT>(); IsValid(UI))
		{
			if (UI->bIsClose)
			{
				UI->DoLoad();
			}
			else
			{
				UI->DoClose();
			}
		}
		else
		{
			LoadUI<WidgetT>(Path);
		}
	}

	// 从列表中移除UI
	void RemoveFromList(UUIBase* ToRemoveUI)
	{
		UIList.Remove(ToRemoveUI);
	}
};
