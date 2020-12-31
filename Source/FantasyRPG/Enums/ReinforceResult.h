#pragma once

#include "CoreMinimal.h"
#include "ReinforceResult.generated.h"

UENUM(BlueprintType)
enum class EReinforceResult : uint8
{
	RF_Success		 UMETA( DisplayName = Success ),
	RF_LackOfMonemy  UMETA( DisplayName = LackOfMoney ),
	RF_Fail			 UMETA( DisplayName = Fail )
};
