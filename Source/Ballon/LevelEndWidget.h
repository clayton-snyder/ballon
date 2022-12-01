// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelEndWidget.generated.h"

/**
 * 
 */
UCLASS()
class BALLON_API ULevelEndWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString AccuracyText;

	UPROPERTY(BlueprintReadOnly)
	FString CompletionText;

	UPROPERTY(BlueprintReadOnly)
	FString TimeElapsedText;

	UPROPERTY(BlueprintReadOnly)
	FName NextLevelName;
};
