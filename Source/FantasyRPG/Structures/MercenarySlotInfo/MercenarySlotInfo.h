#pragma once

#include "CoreMinimal.h"
#include "MercenarySlotInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FMercenarySlotInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		FName MercenaryCode;

	FMercenarySlotInfo();

	FMercenarySlotInfo(FName mercenaryCode);
};