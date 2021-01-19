#pragma once

#include "CoreMinimal.h"
#include "ShopItemType.generated.h"

UENUM(BlueprintType)
enum class EShopItemType : uint8
{
	SI_SaleItem		 UMETA(DisplayName = Sale Item),
	SI_InventoryItem UMETA(DisplayName = Inventory Item)
};
