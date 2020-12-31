#pragma once

#include "CoreMinimal.h"
#include "MonsterType.generated.h"

UENUM(BlueprintType)
enum class EMonsterType : uint8
{
	MT_NORMAL	UMETA (DisplayName = Normal),
	MT_NAMED	UMETA (DisplayName = Named),
	MT_BOSS		UMETA (DisplayName = Boss)
};
