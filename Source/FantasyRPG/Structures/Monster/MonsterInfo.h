#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/MonsterType.h"
#include "MonsterInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FMonsterInfo :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MonsterCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMonsterType MonsterType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkeletalMeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath AnimInstanceClassPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MonsterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> DropItemCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "200.0", ClampMin = "0.0", ClampMax = "200.0"))
	int Lv;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", UIMax = "100000.0", ClampMin = "0.0", ClampMax = "100000.0"))
	float Atk;
};
