#pragma once

#include "CoreMinimal.h"
#include "EquipItemType.generated.h"

UENUM(BlueprintType)
enum class EEquipItemType : uint8
{
	EI_Weapon  UMETA(DisplayName = Weapon),
	EI_Armor   UMETA(DisplayName = Armor)
};
