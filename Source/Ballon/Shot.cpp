// Fill out your copyright notice in the Description page of Project Settings.


#include "Shot.h"
#include "Constants.h"


AShot::AShot()
{
	if (static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(SpherePath); SphereMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMesh.Object);
		Mesh->SetWorldScale3D(FVector(0.03f));
	}

	if (static ConstructorHelpers::FObjectFinder<UMaterial> RedMat(RedMatPath); RedMat.Succeeded())
	{
		EColorToMatInst.Add(GameLogic::EColor::Red, UMaterialInstanceDynamic::Create(RedMat.Object, Mesh));
	} else UE_LOG(LogTemp, Error, TEXT("Could not load Red material!"));

	if (static ConstructorHelpers::FObjectFinder<UMaterial> GreenMat(GreenMatPath); GreenMat.Succeeded())
	{
		EColorToMatInst.Add(GameLogic::EColor::Green, UMaterialInstanceDynamic::Create(GreenMat.Object, Mesh));
	} else UE_LOG(LogTemp, Error, TEXT("Could not load Green material!"));

	if (static ConstructorHelpers::FObjectFinder<UMaterial> ErrMat(ErrMatPath); ErrMat.Succeeded())
	{
		EColorToMatInst.Add(GameLogic::EColor::None, UMaterialInstanceDynamic::Create(ErrMat.Object, Mesh));
	} else UE_LOG(LogTemp, Error, TEXT("Could not load Err material!"));
	
}

void AShot::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay finished."));
}

void AShot::OnHit(
	UPrimitiveComponent* Hitter,
	AActor* StruckActor,
	UPrimitiveComponent* StruckComp,
	FVector NormalImpulse,
	const FHitResult &HitResult)
{
	Super::OnHit(Hitter, StruckActor, StruckComp, NormalImpulse, HitResult);
	UE_LOG(LogTemp, Display, TEXT("AShot OnHit: %s hit %s"), *GetActorNameOrLabel(), *StruckComp->GetName());
}

void AShot::SetColor(const GameLogic::EColor InColor)
{
	Super::SetColor(InColor);
	Mesh->SetMaterial(0, *EColorToMatInst.Find(InColor));
}