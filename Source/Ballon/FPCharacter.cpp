// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFPCharacter::AFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	check(FPCamera != nullptr);
	FPCamera->SetupAttachment(GetRootComponent());
	FPCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight));
	FPCamera->bUsePawnControlRotation = true;

	// Setup the arms-n-hands mesh that should follow camera and only be visible to player
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	check(FPMesh != nullptr);
	FPMesh->SetupAttachment(FPCamera);
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->CastShadow = false;
	FPMesh->bCastDynamicShadow = false;
	GetMesh()->SetOwnerNoSee(true);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjectileSpawn->SetupAttachment(FPCamera);
}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "FPCharacter BeginPlay");
}

// Called every frame
void AFPCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement.Normalize();
	// AddActorLocalOffset(Movement * MoveSpeed);

	check(GEngine != nullptr);
	// const float Length = (Movement * MoveSpeed).Length();
	GEngine->AddOnScreenDebugMessage(23, 1.0f, FColor::Emerald,
	                                 FString::Printf(TEXT("Speed: %.3f"), GetVelocity().Length()));

	if (bCharging)
	{
		ShotCurrCharge = FMath::Min(ShotMaxSpeed, ShotCurrCharge + ShotChargeRate * DeltaTime);
	}
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPCharacter::SetForwardMovement);
	PlayerInputComponent->BindAxis(TEXT("StrafeRight"), this, &AFPCharacter::SetStrafeMovement);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFPCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AFPCharacter::AddControllerYawInput);

	// Actions
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AFPCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AFPCharacter::StartShotCharge);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &AFPCharacter::ReleaseShot);
}

void AFPCharacter::SetForwardMovement(const float Amount)
{
	// Movement.X = Amount;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AFPCharacter::SetStrafeMovement(const float Amount)
{
	// Movement.Y = Amount;
	AddMovementInput(GetActorRightVector(), Amount);
}

void AFPCharacter::StartShotCharge()
{
	ShotCurrCharge = ShotMinSpeed;
	bCharging = true;
}


void AFPCharacter::ReleaseShot()
{
	const FTransform Transform = FTransform(ProjectileSpawn->GetComponentRotation(), ProjectileSpawn->GetComponentLocation());
	AShot* SpawnedShot = GetWorld()->SpawnActorDeferred<AShot>(ClassShot, Transform, this);
	check(SpawnedShot != nullptr);
	SpawnedShot->SetInitAndMaxTravelSpeed(ShotCurrCharge);
	SpawnedShot->SetGravity(0.f);
	SpawnedShot->SetInstigator(GetInstigator());
	SpawnedShot->FinishSpawning(Transform);

	UE_LOG(LogTemp, Display, TEXT("Fired shot with speed: %.1f"), ShotCurrCharge);

	ShotCurrCharge = ShotMinSpeed;
	bCharging = false;
}
