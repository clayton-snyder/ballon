#pragma once

#include "Constants.generated.h"

UCLASS()
class UConstants : public UObject
{
	GENERATED_BODY()
};

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

USTRUCT()
struct FUtil
{
	GENERATED_BODY()
	
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
};