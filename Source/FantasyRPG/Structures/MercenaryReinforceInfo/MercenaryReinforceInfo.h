#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MercenaryReinforceInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FMercenaryReinforceInfo : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MercenaryReinforceCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NextMercenaryReinforceCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float Atk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100.0", ClampMin = "0.0", ClampMax = "100.0"))
	float SkillPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100.0", ClampMin = "0.0", ClampMax = "100.0"))
	float SKillCoolDownTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "10000.0", ClampMin = "0.0", ClampMax = "10000.0"))
	float BuffAtkFigure;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "10000.0", ClampMin = "0.0", ClampMax = "10000.0"))
	float HealingFigure;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ReinforceCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ReinforcementProbability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value3;
};
