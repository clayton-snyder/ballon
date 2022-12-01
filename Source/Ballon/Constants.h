﻿#pragma once
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "ALevelScorer.h"

#include "Constants.generated.h"


inline const TCHAR* SpherePath = TEXT("'/Engine/EngineMeshes/Sphere.Sphere'");
inline const TCHAR* RedMatPath = TEXT("'/Engine/MapTemplates/Materials/BasicAsset01.BasicAsset01'");
inline const TCHAR* GreenMatPath = TEXT("'/Engine/MapTemplates/Materials/BasicAsset03.BasicAsset03'");
inline const TCHAR* ErrMatPath = TEXT("'/Engine/EditorMeshes/ColorCalibrator/M_ColorGrid.M_ColorGrid'");

#pragma region ENUMS

UENUM(BlueprintType)
namespace GameLogic
{
	enum EColor
	{
		None,
		Red,
		Green,
	};
}

#pragma endregion ENUMS

UCLASS()
class UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	inline static const TCHAR* TagShot = TEXT("SHOT");
	inline static const TCHAR* TagPoppable = TEXT("POPPABLE");
	inline static const TCHAR* TagGrapple = TEXT("GRAPPLE");
	inline static const TCHAR* TagStickyMine = TEXT("STICKY_MINE");


	UFUNCTION(BlueprintCallable, Category = "BallonConstants")
	static FName GetTagShot() { return FName(TagShot); }

	UFUNCTION(BlueprintCallable, Category = "BallonConstants")
	static FName GetTagPoppable() { return FName(TagPoppable); }

	UFUNCTION(BlueprintCallable, Category = "BallonConstants")
	static FName GetTagGrapple() { return FName(TagGrapple); }

	UFUNCTION(BlueprintCallable, Category = "BallonConstants")
	static FName GetTagStickyMine() { return FName(TagStickyMine); }


	////////////// UTILITY //////////////
	UFUNCTION(BlueprintCallable, Category = "BallonUtility")
	static FString EColorToString(const GameLogic::EColor Color)
	{
		switch (Color)
		{
		case GameLogic::EColor::Green:
			return "Green";
		case GameLogic::EColor::Red:
			return "Red";
		case GameLogic::EColor::None:
			return "None";
		}

		return "Unknown";
	}

	UFUNCTION(BlueprintCallable, Category = "BallonUtility")
	static FLinearColor EColorToFLinearColor(const GameLogic::EColor Color)
	{
		switch (Color)
		{
		case GameLogic::EColor::Green:
			return FLinearColor(0.f, 1.f, 0.f, 1.f);
		case GameLogic::EColor::Red:
			return FLinearColor(1.f, 0.2f, 0.f, 1.f);
		case GameLogic::EColor::None:
			return FLinearColor::White;
		}

		return FLinearColor::Black;
	}
};