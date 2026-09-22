// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataFunc.generated.h"

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDataFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static FString StdToFString(const std::string& InString)
	{
		return UTF8_TO_TCHAR(InString.c_str());
	}

	static std::string FStringToStd(const FString& InString)
	{
		return TCHAR_TO_UTF8(*InString);
	}

	static FString IntToFString(const int32 InInt)
	{
		return FString::FromInt(InInt);
	}

	static int32 FStringToInt(const FString& InString)
	{
		return FCString::Atoi(*InString);
	}

	static FString FloatToFString(const float InFloat)
	{
		return FString::SanitizeFloat(InFloat);
	}

	static float FStringToFloat(const FString& InString)
	{
		return FCString::Atof(*InString);
	}

	// 获取枚举名称
	template<typename T>
	static FString GetEnumName(T EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<T>();
		return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
	}

	// 获取枚举全部名称
	template<typename T>
	static FString GetEnumFullName(const T EnumValue)
	{
		return UEnum::GetValueAsString(EnumValue);
	}
};
