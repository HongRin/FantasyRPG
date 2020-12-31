#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MercenaryInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FMercenaryInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MercenaryCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MercenaryReinforceCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkeletalMeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath AnimInstanceClassPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MercenaryName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float Atk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100.0", ClampMin = "0.0", ClampMax = "100.0"))
	float SkillPercentage;
};
