// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ALevelScorer.h"
#include "LevelEndWidget.h"
#include "GameFramework/GameModeBase.h"
#include "BallonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BALLON_API ABallonGameModeBase : public AGameModeBase
{

	GENERATED_BODY()

	virtual void StartPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void DisplayLevelEndWidget(FLevelScore Score);

	UFUNCTION(BlueprintCallable)
	FName GetNextLevel(FString CurrLevel);

protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI")
	// TSubclassOf<UUserWidget> LevelEndWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", Meta = (BlueprintProtected = "true"))
	TSubclassOf<ULevelEndWidget> LevelEndClass;
};