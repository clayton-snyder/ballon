// Fill out your copyright notice in the Description page of Project Settings.


#include "GI.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UGI::UGI() {}

bool UGI::PlayBGMusic()
{
	if (IsMusicPlaying) return false;

	check(BGMusicWorldA != nullptr);
	UAudioComponent* BGMusicAudioComponent = UGameplayStatics::SpawnSound2D(
		this, BGMusicWorldA, 1, 1, 0,
		nullptr, true, true);
	check(BGMusicAudioComponent != nullptr);
	BGMusicAudioComponent->Play();
	IsMusicPlaying = true;
	
	return true;
}

void UGI::PlayFailSound()
{
	check(FailSound != nullptr);
	UAudioComponent* FailSoundAudioComponent = UGameplayStatics::SpawnSound2D(
		this, FailSound, 1, 1, 0,
		nullptr, true, true);
	check(FailSoundAudioComponent != nullptr);
	FailSoundAudioComponent->Play();
}

void UGI::PlayDingSound()
{
	check(DingSound != nullptr);
	UAudioComponent* DingSoundAudioComponent = UGameplayStatics::SpawnSound2D(
		this, DingSound, 1, 1, 0,
		nullptr, true, true);
	check (DingSoundAudioComponent != nullptr);
	DingSoundAudioComponent->Play();
}

void UGI::PlayShootSound()
{
	check(ShootSound != nullptr);
	UAudioComponent* ShootSoundAudioComponent = UGameplayStatics::SpawnSound2D(
		this, ShootSound, 1, 1, 0,
		nullptr, true, true);
	check (ShootSoundAudioComponent != nullptr);
	ShootSoundAudioComponent->Play();
}
