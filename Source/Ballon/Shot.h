// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "Constants.h"
#include "Shot.generated.h"

/**
 * 
 */
UCLASS()
class BALLON_API AShot : public ABaseProjectile
{
	GENERATED_BODY()

public:
	AShot();

	EGameLogic::EGLColor GetColor() const;
	void SetColor(const EGameLogic::EGLColor InColor);

	
protected:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EGameLogic::EGLColor> Color = EGameLogic::Red;
	
	void BeginPlay() override;

	void OnHit(
		UPrimitiveComponent* Hitter,
		AActor* StruckActor,
		UPrimitiveComponent* StruckComp,
		FVector NormalImpulse,
		const FHitResult &HitResult) override;
	
};
