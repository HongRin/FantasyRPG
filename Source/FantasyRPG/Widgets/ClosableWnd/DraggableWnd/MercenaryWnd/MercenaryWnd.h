#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "MercenaryWnd.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryWnd : public UDraggableWnd
{
	GENERATED_BODY()
	
public:
	UMercenaryWnd(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;

};
