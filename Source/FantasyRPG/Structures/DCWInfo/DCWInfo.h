#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DCWInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FDCWInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
	FName DCWCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> DungeonRowCode;
};
