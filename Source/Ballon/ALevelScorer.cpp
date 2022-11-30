// Fill out your copyright notice in the Description page of Project Settings.


#include "ALevelScorer.h"

#include "FPCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelScorer::ALevelScorer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelScorer::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AFPCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(Player != nullptr);

	FIncrementShotsFiredDelegate ShotsDelegate;
	ShotsDelegate.BindUObject(this, &ALevelScorer::IncrementShotsFired);
	Player->OnShotFired.Add(ShotsDelegate);

	FIncrementNumPoppedDelegate NumPoppedDelegate;
	NumPoppedDelegate.BindUObject(this, &ALevelScorer::IncrementNumPopped);
	

	TArray<AActor*> Poppables;
	UGameplayStatics::GetAllActorsWithTag(this, UConstants::TagPoppable, Poppables);
	TotalPoppable = Poppables.Num();

	UE_LOG(LogTemp, Display, TEXT("Init TotalPoppable to: %d"), TotalPoppable);

	TimeElapsed = 0.f;
}

void ALevelScorer::IncrementShotsFired()
{
	ShotsFired++;
	UE_LOG(LogTemp, Display, TEXT("Incremented ShotsFired"));
}

void ALevelScorer::IncrementNumPopped()
{
	NumPopped++;
	UE_LOG(LogTemp, Display, TEXT("Incremented NumPopped"));
}


FLevelScore ALevelScorer::GetScore() const
{
	FLevelScore Score;
	Score.TimeElapsed = TimeElapsed;
	Score.ShotsFired = ShotsFired;
	Score.TotalPoppable = TotalPoppable;
	Score.NumPopped = NumPopped;
	
	return Score;
}

// Called every frame
void ALevelScorer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeElapsed += DeltaTime;
}
