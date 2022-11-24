// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shot.h"
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	////  STRUCTURE  ////
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FPCamera;

	// This is for the arms-n-hands mesh visible only to player
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* FPMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawn;
	//////////////////////////////////////////////////////////////////////



	////  ATTRIBUTES  ////
	// UPROPERTY(EditAnywhere, Category="Movement")
	// float MoveSpeed = 15.f;
	//
	// UPROPERTY(EditAnywhere, Category="Movement")
	// float JumpStrength = 150.f;
	//////////////////////////////////////////////////////////////////////

	
	//// PROJECTILES  ////
	UPROPERTY(EditAnywhere, Category="Projectiles")
	TSubclassOf<AShot> ClassShot;

	UPROPERTY(EditAnywhere, Category="Projectiles")
	TEnumAsByte<GameLogic::EColor> ProjectileColor = GameLogic::EColor::Green;
	
	// If no charge
	UPROPERTY(EditAnywhere, Category="Projectiles")
	float ShotMaxSpeed = 10000.f;

	// If max charge
	UPROPERTY(EditAnywhere, Category="Projectiles")
	float ShotMinSpeed = 1000.f;
	float ShotCurrCharge = ShotMinSpeed;
	
	UPROPERTY(EditAnywhere, Category="Projectiles")
	float ShotFullChargeSeconds = 2.f;
	float ShotChargeRate = (ShotMaxSpeed - ShotMinSpeed) / ShotFullChargeSeconds;
	bool bCharging = false;

public:	
	// Called every frame
	virtual void Tick(const float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetForwardMovement(const float Amount);
	void SetStrafeMovement(const float Amount);

	// Actions
	void ReleaseShot();
	void StartShotCharge();
};
