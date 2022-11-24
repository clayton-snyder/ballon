// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoToneFloater.h"

// Sets default values
ATwoToneFloater::ATwoToneFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	MeshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshA"));
	MeshA->SetupAttachment(Scene);
	
	MeshB = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshB"));
	MeshB->SetupAttachment(Scene);
}

// Called when the game starts or when spawned
void ATwoToneFloater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATwoToneFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

