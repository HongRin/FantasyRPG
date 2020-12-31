#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "StatusWnd.generated.h"

UCLASS()
class FANTASYRPG_API UStatusWnd : public UDraggableWnd
{
	GENERATED_BODY()

private :
	class UTextBlock* Text_StatPoint;
	
private :
	void NativeConstruct() override;

public :
	void UpdateStatPointText(FText text);
};
