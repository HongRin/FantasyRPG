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
	// �巡���� �����ϴ� ������ ��Ÿ���ϴ�.
	UItemSlot* DraggingSlot;
	
};
