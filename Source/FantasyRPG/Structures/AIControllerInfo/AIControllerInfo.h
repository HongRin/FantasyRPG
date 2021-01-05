#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AIControllerInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FAIControllerInfo : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AIControllerCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SightRadius = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LoseSightRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PeripheralVisionAngleDegrees = 180.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxAge;
};
