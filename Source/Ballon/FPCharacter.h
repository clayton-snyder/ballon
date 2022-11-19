// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"

UCLASS()
class BALLON_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FPCamera;

	// This is for the arms-n-hands mesh visible only to player
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FPMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Movement;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed = 15.f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float JumpStrength = 150.f;

public:	
	// Called every frame
	virtual void Tick(const float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetForwardMovement(const float Amount);
	void SetStrafeMovement(const float Amount);
};
