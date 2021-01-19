#pragma once

#include "CoreMinimal.h"
#include "ShopType.generated.h"

UENUM(BlueprintType)
enum class EShopType : uint8
{
	ST_NONE			UMETA(DisplayName = NoneShop),
	ST_ITEM			UMETA(DisplayName = ItemShop),
	ST_MERCENARY	UMETA(DisplayName = MercenaryShop)
};
