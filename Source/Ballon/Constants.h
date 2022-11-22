#pragma once

#include "Constants.generated.h"

UCLASS()
class UConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

#pragma region ENUMS

UENUM(BlueprintType)
namespace EGameLogic
{
	enum EGLColor
	{
		None,
		Red,
		Green,
	};
}

#pragma endregion ENUMS