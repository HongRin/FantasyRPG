#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DungeonRowInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FDungeonRowInfo : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName DungeonCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText DungeonName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName NextMapName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FSoftObjectPath DungeonSpritePath;
};
