#pragma once

#include "CoreMinimal.h"
#include "ItemSlotInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FItemSlotInfo
{
	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY()
	FName ItemCode;

	UPROPERTY()
	int32 ItemCount;

public :
	FItemSlotInfo();
	FItemSlotInfo(FName itemCode, int32 itemCount);

	FORCEINLINE bool IsEmpty() const
	{
		return (ItemCode == FName(TEXT("None")));
	}

	FORCEINLINE void AddItemCount(int32 count)
	{
		ItemCount += count;
	}

	FORCEINLINE bool operator==(const FItemSlotInfo& itemSlotInfo) const
	{
		return (ItemCode == itemSlotInfo.ItemCode) && ItemCount == itemSlotInfo.ItemCount;
	}

	FORCEINLINE bool operator!=(const FItemSlotInfo& itemSlotInfo) const
	{
		return (ItemCode != itemSlotInfo.ItemCode) || ItemCount != itemSlotInfo.ItemCount;
	}
};