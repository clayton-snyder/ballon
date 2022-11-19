// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFPCharacter::AFPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	check(FPCamera != nullptr);
	FPCamera->SetupAttachment(GetRootComponent());
	FPCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight + 45.f));
	FPCamera->bUsePawnControlRotation = true;

	// Setup the arms-n-hands mesh that should follow camera and only be visible to player
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FPMesh");
	check(FPMesh != nullptr);
	FPMesh->SetupAttachment(FPCamera);
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->CastShadow = false;
	FPMesh->bCastDynamicShadow = false;

	GetMesh()->SetOwnerNoSee(true);
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

	Movement.Normalize();
	AddActorLocalOffset(Movement * MoveSpeed);

	check(GEngine != nullptr);
	const float Length = (Movement * MoveSpeed).Length();
	GEngine->AddOnScreenDebugMessage(23, 1.0f, FColor::Emerald,
		FString::Printf(TEXT("Speed: %.3f"), Length));
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPCharacter::SetForwardMovement);
	PlayerInputComponent->BindAxis(TEXT("StrafeRight"), this, &AFPCharacter::SetStrafeMovement);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AFPCharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFPCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AFPCharacter::AddControllerYawInput);
}

void AFPCharacter::SetForwardMovement(const float Amount)
{
	Movement.X = Amount;
}

void AFPCharacter::SetStrafeMovement(const float Amount)
{
	Movement.Y = Amount;
}
