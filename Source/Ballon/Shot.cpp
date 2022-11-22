// Fill out your copyright notice in the Description page of Project Settings.


#include "Shot.h"
#include "Constants.h"

const TCHAR* SpherePath = TEXT("'/Engine/EngineMeshes/Sphere.Sphere'");
const TCHAR* RedMatPath = TEXT("'/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01'");
const TCHAR* GreenMatPath = TEXT("'/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03'");
const TCHAR* ErrMatPath = TEXT("'/Engine/EditorMeshes/ColorCalibrator/M_ColorGrid.M_ColorGrid'");

AShot::AShot()
{

	if (static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(SpherePath); SphereMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMesh.Object);
		Mesh->SetWorldScale3D(FVector(0.03f));
	}

	switch (Color)
	{
	case EGameLogic::Red:
		if (static ConstructorHelpers::FObjectFinder<UMaterial> RedMat(RedMatPath); RedMat.Succeeded())
		{
			auto MatInstance = UMaterialInstanceDynamic::Create(RedMat.Object, Mesh);
			Mesh->SetMaterial(0, MatInstance);
		}
		break;
	case EGameLogic::Green:
		if (static ConstructorHelpers::FObjectFinder<UMaterial> GreenMat(GreenMatPath); GreenMat.Succeeded())
		{
			auto MatInstance = UMaterialInstanceDynamic::Create(GreenMat.Object, Mesh);
			Mesh->SetMaterial(0, MatInstance);
		}
		break;
	case EGameLogic::None:
		if (static ConstructorHelpers::FObjectFinder<UMaterial> ErrMat(ErrMatPath); ErrMat.Succeeded())
		{
			auto MatInstance = UMaterialInstanceDynamic::Create(ErrMat.Object, Mesh);
			Mesh->SetMaterial(0, MatInstance);
		}
		break;
	default:
		UE_LOG(LogTemp, Fatal, TEXT("COULD NOT LOAD COLOR MATERIAL"));
	}
}

void AShot::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShot::OnHit(
	UPrimitiveComponent* Hitter,
	AActor* StruckActor,
	UPrimitiveComponent* StruckComp,
	FVector NormalImpulse,
	const FHitResult &HitResult)
{
	Super::OnHit(Hitter, StruckActor, StruckComp, NormalImpulse, HitResult);
	UE_LOG(LogTemp, Display, TEXT("AShot OnHit: %s hit %s"), *GetActorNameOrLabel(), *StruckComp->GetName());
}

EGameLogic::EGLColor AShot::GetColor() const
{
	return this->Color;
}

void AShot::SetColor(const EGameLogic::EGLColor InColor)
{
	this->Color = InColor;
}

