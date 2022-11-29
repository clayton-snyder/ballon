// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI.generated.h"

/**
 * 
 */
UCLASS()
class BALLON_API UGI : public UGameInstance
{
	GENERATED_BODY()

public:
	UGI();

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
