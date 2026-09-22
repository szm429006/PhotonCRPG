// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataFunc.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhotonCRPG/PhotonCRPGPlayerController.h"
#include "PhotonCRPG/Public/PhotonCRPGGameState.h"
#include "Data/GlobalEnum.h"
#include "Kismet/GameplayStatics.h"
#include "PhotonCRPG/PhotonCRPGGameMode.h"
#include "Character/CharacterBase.h"
#include "GlobalFunc.generated.h"

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UGlobalFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template<typename TargetClass = UGameInstanceSubsystem>
	static TargetClass* GetSubsystem()
	{
		static TWeakObjectPtr<TargetClass> CachedSubsystem;

		if (CachedSubsystem.IsValid())
		{
			//UE_LOG(LogTemp, Warning, TEXT("Subsystem 初始化, %s"), *CachedSubsystem->GetClass()->GetName());
			return CachedSubsystem.Get();
		}

		if (!GEngine || !GEngine->GameViewport)
			return nullptr;

		const auto World = GEngine->GameViewport->GetWorld();
		if (!IsValid(World))
			return nullptr;

		const auto GameInstance = World->GetGameInstance();
		if (!IsValid(GameInstance))
			return nullptr;

		TargetClass* Subsystem = GameInstance->GetSubsystem<TargetClass>();
		CachedSubsystem = Subsystem;
		return Subsystem;
	}

	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static ACharacterBase* GetPlayer()
	{
		return GetController()->GetCurCharacter();
	}

	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static int32 GetPlayerCoreAttr(const ECoreAttrType AttrType)
	{
		const auto CoreAttributeSet = Cast<UCoreAttributeSet>(GetPlayer()->GetAbilityComp()->GetAttributeSet(UCoreAttributeSet::StaticClass()));
		
	}

	// 游戏模式
	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static APhotonCRPGGameMode* GetGameMode()
	{
		static TWeakObjectPtr<APhotonCRPGGameMode> CachedGameMode;

		if (CachedGameMode.IsValid())
		{
			// UE_LOG(LogTemp, Warning, TEXT("APhotonCRPGGameMode 有缓存"));
			return CachedGameMode.Get();
		}

		if (!GEngine || !GEngine->GameViewport)
			return nullptr;

		const auto World = GEngine->GameViewport->GetWorld();
		if (!IsValid(World))
			return nullptr;

		APhotonCRPGGameMode* GameMode = Cast<APhotonCRPGGameMode>(UGameplayStatics::GetGameMode(World));
		CachedGameMode = GameMode;
		return GameMode;
	}

	// 获取当前玩家控制器
	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static APhotonCRPGPlayerController* GetController()
	{
		static TWeakObjectPtr<APhotonCRPGPlayerController> CachedController;

		if (CachedController.IsValid())
		{
			// UE_LOG(LogTemp, Warning, TEXT("APhotonCRPGController 有缓存"));
			return CachedController.Get();
		}

		if (!GEngine || !GEngine->GameViewport)
			return nullptr;

		const auto World = GEngine->GameViewport->GetWorld();
		if (!IsValid(World))
			return nullptr;

		APhotonCRPGPlayerController* PlayerController = Cast<APhotonCRPGPlayerController>(World->GetFirstPlayerController());
		CachedController = PlayerController;
		return PlayerController;
	}

	// 获取玩家状态
	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static APhotonCRPGGameState* GetGameState()
	{
		static TWeakObjectPtr<APhotonCRPGGameState> CachedGameState;

		if (CachedGameState.IsValid())
		{
			// UE_LOG(LogTemp, Warning, TEXT("APhotonCRPGGameState 有缓存"));
			return CachedGameState.Get();
		}

		if (!GEngine || !GEngine->GameViewport)
			return nullptr;

		const auto World = GEngine->GameViewport->GetWorld();
		if (!IsValid(World))
			return nullptr;

		APhotonCRPGGameState* GameState = Cast<APhotonCRPGGameState>(UGameplayStatics::GetGameState(World));
		CachedGameState = GameState;
		return GameState;
	}

	// 设置当前游戏状态
	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static void SetGameStateType(const EGameStateType Type)
	{
		const auto GameState = GetGameState();
		if (IsValid(GameState))
		{
			GameState->SetGameStateType(Type);
		}
	}

	// 获取当前游戏状态
	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static EGameStateType GetGameStateType()
	{
		const auto GameState = GetGameState();
		if (IsValid(GameState))
		{
			return GameState->GetGameStateType();
		}
		return EGameStateType::Normal;
	}

	static UTexture2D* GetCachedIcon(const FString& IconName)
	{
		static TMap<FString, TWeakObjectPtr<UTexture2D>> CachedIcons;
		if (!CachedIcons.Contains(IconName))
		{
			// UE_LOG(LogTemp, Warning, TEXT("没有缓存图标: %s"), *IconName);
			const auto IconResoure = LoadObject<UTexture2D>(nullptr, *IconName);
			if (IsValid(IconResoure))
			{
				// UE_LOG(LogTemp, Warning, TEXT("有图标资源"));
				CachedIcons.Add(IconName, IconResoure);
				return IconResoure;
			}
			// UE_LOG(LogTemp, Warning, TEXT("没有图标资源"));
			return nullptr;
		}
		// UE_LOG(LogTemp, Warning, TEXT("已有缓存图标: %s"), *IconName);
		return CachedIcons[IconName].Get();
	}

	// 从路径加载BPActor
	template<typename TargetClass>
	static TargetClass* SpawnBPActor(const FString& Folder, const FString& ActorName, const FTransform& Transform)
	{
		if (!GEngine || !GEngine->GameViewport)
			return nullptr;
		
		const auto World = GEngine->GameViewport->GetWorld();
		if (!IsValid(World))
			return nullptr;
		
		const FString Path = FString::Printf(TEXT("/Script/Engine.Blueprint'/Game/%s/%s.%s_C'"), *Folder, *ActorName, *ActorName);
		const auto ActorClass = LoadClass<AActor>(nullptr, *Path);
		if (IsValid(ActorClass))
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			return World->SpawnActor<TargetClass>(ActorClass, Transform, SpawnParams);
		}
		
		return nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = "GlobalFunc")
	static FString GetLocName(const FString& InStrLocID)
	{
		const auto TbLocData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbLocalizationData(InStrLocID);
		if (TbLocData != nullptr)
		{
			return UDataFunc::StdToFString(TbLocData->cn);
		}

		return "";
	}

	template<typename T>
	static FString GetLocNameByEnum(T EnumValue)
	{
		const FString EnumName = UDataFunc::GetEnumName<T>(EnumValue);
		const auto TbLocData = UGlobalFunc::GetSubsystem<UDataSystem>()->GetTbLocalizationData(EnumName);
		if (TbLocData != nullptr)
		{
			return UDataFunc::StdToFString(TbLocData->cn);
		}

		return "";
	}
};
