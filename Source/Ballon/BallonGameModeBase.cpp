// Copyright Epic Games, Inc. All Rights Reserved.


#include "BallonGameModeBase.h"

void ABallonGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Yellow, TEXT("This is BallonGameMode."));
}