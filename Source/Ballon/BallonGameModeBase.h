// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
};