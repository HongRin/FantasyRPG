#pragma once

#include "CoreMinimal.h"
#include "ItemRatingType.generated.h"

UENUM(BlueprintType)
enum class EItemRatingType : uint8
{
	RT_NORMAL	UMETA(DisplayName = Normal),
	RT_RARE		UMETA(DisplayName = Rare),
	RT_UNIQUE	UMETA(DisplayName = Unique),
	RT_EPIC		UMETA(DisplayName = Epic)

};
