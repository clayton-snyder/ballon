// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoToneFloater.h"

#include "ALevelScorer.h"
#include "FPCharacter.h"
#include "GI.h"
#include "BaseProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATwoToneFloater::ATwoToneFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	MeshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshA"));
	MeshA->SetupAttachment(Scene);
	
	MeshB = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshB"));
	MeshB->SetupAttachment(Scene);

	Tags.Add(UConstants::TagPoppable);
}

// Called when the game starts or when spawned
void ATwoToneFloater::BeginPlay()
{
	Super::BeginPlay();
	
	MeshA->OnComponentHit.AddDynamic(this, &ATwoToneFloater::OnHit);
	MeshB->OnComponentHit.AddDynamic(this, &ATwoToneFloater::OnHit);

	Player = Cast<AFPCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	check(Player != nullptr);

	GI = Cast<UGI>(GetGameInstance());
	check(GI != nullptr);

	TArray<AActor*> Scorer;
	UGameplayStatics::GetAllActorsOfClass(this, ALevelScorer::StaticClass(), Scorer);
	if (Scorer.Num() != 1)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Found %d LevelScorers, expected exactly 1."), Scorer.Num());
	}

	LevelScorer = Cast<ALevelScorer>(Scorer[0]);
	check(LevelScorer != nullptr);

}

// Called every frame
void ATwoToneFloater::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATwoToneFloater::OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& HitResult)
{
	if (!OtherActor->ActorHasTag(UConstants::TagShot)) return;
	if (AlreadyStruck)
	{
		UE_LOG(LogTemp, Display, TEXT("%s OnHit() was already hit, ignoring"), *GetActorNameOrLabel());
		return;
	}
	AlreadyStruck = true;
	UE_LOG(LogTemp, Display, TEXT("TwoToneFloater OnHit(HitComp=%s, OtherActor=%s, OtherComp=%s)"),
		*HitComp->GetName(), *OtherActor->GetActorNameOrLabel(), *OtherComp->GetName());
	const ABaseProjectile* Projectile = Cast<ABaseProjectile>(OtherActor);
	if (Projectile == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("OnHit cast failed; %s not a ABaseProjectile."), *OtherActor->GetActorNameOrLabel());
		return;
	}
	if (Projectile->ActorHasTag(UConstants::TagShot))
	{
		if (Projectile->GetColor() == ColorA || Projectile->GetColor() == ColorB)
		{
			GI->PlayDingSound();
			Player->SetProjectileColor(Projectile->GetColor() == ColorA ? ColorB : ColorA);
			LevelScorer->IncrementNumPopped();
		} else
		{
			GI->PlayFailSound();
			UE_LOG(LogTemp, Error, TEXT("~~~~~~~~~~~~~PLAYER LOSE"));
			// TODO: Track failures?
			UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
		}
		Destroy();
	}

	if (Projectile->ActorHasTag(UConstants::TagGrapple))
	{
		// Stub...
	}

	if (Projectile->ActorHasTag(UConstants::TagStickyMine))
	{
		// Stub...
	}
}