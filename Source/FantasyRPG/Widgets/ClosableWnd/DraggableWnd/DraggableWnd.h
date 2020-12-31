#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "DraggableWnd.generated.h"

UCLASS()
class FANTASYRPG_API UDraggableWnd : public UClosableWnd
{
	GENERATED_BODY()
	
private:
	class UDraggableWndTitle* BP_DraggableWndTitle;

protected:
	virtual void NativeOnInitialized() override;
};
