// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI.generated.h"

USTRUCT(BlueprintType)
struct FLevelHiScore
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bLocked;

	UPROPERTY(BlueprintReadOnly)
	float BestTime;

	UPROPERTY(BlueprintReadOnly)
	float BestAccuracy;

	FLevelHiScore() { bLocked = true; BestTime = -1.f; BestAccuracy = -1.f; }
	FLevelHiScore(const bool bInLocked, const float InBestTime, const float InBestAccuracy)
	{
		bLocked = bInLocked;
		BestTime = InBestTime;
		BestAccuracy = InBestAccuracy;
	}
};

/**
 * 
 */
UCLASS()
class BALLON_API UGI : public UGameInstance
{
	GENERATED_BODY()

public:
	UGI();

	UFUNCTION(BlueprintCallable)
	FLevelHiScore GetLevelHiScore(const FString LevelName);

	UFUNCTION(BlueprintCallable)
	void SaveLevelScoreIfHighest(const FString LevelName, const FLevelScore Score);
	

	////////////////// SOUND
	// Returns false and has no effect if music is already playing
	UFUNCTION(BlueprintCallable, Category = "Sound")
	bool PlayBGMusic();

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayFailSound();

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayDingSound();

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayShootSound();

protected:
	TMap<FString, FLevelHiScore> HiScores;
	void LoadHiScores();

	
	////////////////// SOUND
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* BGMusicWorldA;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsMusicPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* FailSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* DingSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* ShootSound;
};
