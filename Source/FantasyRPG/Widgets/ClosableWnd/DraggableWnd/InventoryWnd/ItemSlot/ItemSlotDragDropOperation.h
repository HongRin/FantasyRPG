#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemSlot.h"
#include "ItemSlotDragDropOperation.generated.h"

UCLASS()
class FANTASYRPG_API UItemSlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public :
	// 드래깅을 시작하는 슬롯을 나타냅니다.
	UItemSlot* DraggingSlot;
	
};
