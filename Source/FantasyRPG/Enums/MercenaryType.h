#pragma once

#include "CoreMinimal.h"
#include "MercenaryType.generated.h"

UENUM(BlueprintType)
enum class EMercenaryType : uint8
{
	MCT_KNIGHT		UMETA(DisplayName = Kinght),
	MCT_HEALER		UMETA(DisplayName = Healer),
};
