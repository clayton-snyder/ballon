// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Constants.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseProjectile.generated.h"

UCLASS()
class BALLON_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Logic")
	UMaterial* GreenMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Logic")
	UMaterial* RedMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Logic")
	UMaterial* ErrMat;
	
	
	////////////// STRUCTURE //////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* Movement;

	// Another way to do this is just to set InitialLifeSpan (destroy after time instead of distance)
	UPROPERTY()
	float DestroyAfterTravelDist = 100000.f;
	FVector StartLoc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<GameLogic::EColor> Color;
	///////////////////////////////////////

	UFUNCTION()
	virtual void OnHit(
		UPrimitiveComponent* Hitter,
		AActor* StruckActor,
		UPrimitiveComponent* StruckComp,
		FVector NormalImpulse,
		const FHitResult &HitResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This will have no effect if called after the Actor is spawned. Call before FinishSpawning().
	float SetInitAndMaxTravelSpeed(float Speed);

	// This will have no effect if called after the Actor is spawned. Call before FinishSpawning().
	float SetGravity(float Gravity);
	
	GameLogic::EColor GetColor() const;
	virtual void SetColor(const GameLogic::EColor InColor);

};
