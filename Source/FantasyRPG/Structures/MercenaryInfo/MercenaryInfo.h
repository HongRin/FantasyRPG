#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/MercenaryType.h"
#include "AnimInstances/MercenaryCharacter/MercenaryAnimInstance.h"
#include "Actors/Controllers/MercenaryController/MercenaryController.h"
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
	TSubclassOf<UMercenaryAnimInstance> AnimInstanceClassPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAIController> MercenaryControllerClassPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath MercernaryIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MercenaryName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMercenaryType MercenaryType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
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
	int32 Cost;

	// 기타 수치
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value3;
};

