// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Constants.h"
#include "Balloon.generated.h"


UCLASS()
class BALLON_API ABalloon : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ABalloon();

	GameLogic::EColor GetColor() const;
	void SetColor(const GameLogic::EColor Color);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	GameLogic::EColor Color;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TMap<GameLogic::EColor, UMaterialInstance*> EColorToMatInst;
		
};