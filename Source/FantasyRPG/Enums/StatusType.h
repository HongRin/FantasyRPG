#pragma once

#include "CoreMinimal.h"
#include "StatusType.generated.h"

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	ST_Atk		UMETA( DisplayName = Atk),
	ST_Def		UMETA( DisplayName = Def),
	ST_Hp		UMETA( DisplayName = Hp),
	ST_Mp		UMETA( DisplayName = Mp)
};
