// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetNotifyRigidBodyCollision(true);
	RootComponent = Mesh;

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereTest");
	CollisionComponent->InitSphereRadius(15.f);
	CollisionComponent->BodyInstance;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);

	StartLoc = GetActorLocation();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay finished"));
	
}

// Called every frame
void ABaseProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if-init syntax cooL!!!
	if (const float TravelDist = (GetActorLocation() - StartLoc).Length(); TravelDist >= DestroyAfterTravelDist)
	{
		Destroy();
		UE_LOG(LogTemp, Display, TEXT("%s destroyed after travelling %.1f"), *GetActorNameOrLabel(), TravelDist);
	}
}

void ABaseProjectile::OnHit(
	UPrimitiveComponent* Hitter,
	AActor* StruckActor,
	UPrimitiveComponent* StruckComp,
	FVector NormalImpulse,
	const FHitResult &HitResult)
{
	UE_LOG(LogTemp, Display, TEXT("OnHit from BaseProjectile. Struck: %s"), *StruckActor->GetActorNameOrLabel())
}

float ABaseProjectile::SetInitAndMaxTravelSpeed(const float Speed)
{
	Movement->MaxSpeed = Speed;
	Movement->InitialSpeed = Speed;
	return Speed;
}

float ABaseProjectile::SetGravity(float Gravity)
{
	Movement->ProjectileGravityScale = Gravity;
	return Gravity;
}