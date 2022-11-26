// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Constants.h"
#include "GameFramework/Actor.h"
#include "TwoToneFloater.generated.h"

UCLASS()
class BALLON_API ATwoToneFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATwoToneFloater();

protected:
	bool AlreadyStruck = false;
	class AFPCharacter* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Logic")
	UMaterial* GreenMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Logic")
	UMaterial* RedMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Logic")
	UMaterial* ErrMat;
	
	
	////////////// STRUCTURE //////////////
	// Having a bare scene component as root allows MeshA and MeshB to be siblings, each a child
	// of this root. Neither Mesh has the additional responsibility of being the primary transform.
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Scene;
	
	// MeshA and MeshB should each have a color associated.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Color Logic")
	TEnumAsByte<GameLogic::EColor> ColorA;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Color Logic")
	TEnumAsByte<GameLogic::EColor> ColorB;
	///////////////////////////////////////


	UFUNCTION()
	virtual void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& HitResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
