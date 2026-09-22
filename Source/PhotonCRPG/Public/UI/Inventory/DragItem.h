// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragItem.generated.h"

class UItemObject;
class UImage;

/**
 * 
 */
UCLASS()
class PHOTONCRPG_API UDragItem : public UUserWidget
{
	GENERATED_BODY()
		
protected:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Icon;

public:

	void SetContent(const UItemObject* InItem) const;
};
