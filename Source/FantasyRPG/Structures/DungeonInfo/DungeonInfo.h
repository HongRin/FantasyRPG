#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DungeonInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FDungeonInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DungeonCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MonsterCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ExistBoss;
};
