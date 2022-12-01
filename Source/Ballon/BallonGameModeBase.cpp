// Copyright Epic Games, Inc. All Rights Reserved.


#include "BallonGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABallonGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Yellow, TEXT("This is BallonGameMode."));
}

void ABallonGameModeBase::DisplayLevelEndWidget(FLevelScore Score)
{
	ULevelEndWidget* NewWidget = CreateWidget<ULevelEndWidget>(GetWorld(), LevelEndClass);
	NewWidget->AccuracyText = FString::Printf(
		TEXT("%.1f%% Accuracy"), static_cast<float>(Score.NumPopped) / Score.ShotsFired * 100);
	NewWidget->CompletionText = FString::Printf(TEXT("%d out of %d"), Score.NumPopped, Score.TotalPoppable);
	NewWidget->TimeElapsedText = FString::Printf(TEXT("%.2fs"), Score.TimeElapsed);
	NewWidget->AddToViewport();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	UGameplayStatics::GetPlayerPawn(this, 0)->DisableInput(Controller);
	Controller->bShowMouseCursor = true;
	NewWidget->bIsFocusable = true;
	NewWidget->SetFocus();
}

FName ABallonGameModeBase::GetNextLevel(FString CurrLevel)
{
	if (CurrLevel == "Sandbox") return "Sandbox2";
	if (CurrLevel == "Sandbox2") return "Sandbox";
	UE_LOG(LogTemp, Error, TEXT("UNKNOWN LEVEL NAME: %s"), *CurrLevel);
	return "UNKNOWN";
}