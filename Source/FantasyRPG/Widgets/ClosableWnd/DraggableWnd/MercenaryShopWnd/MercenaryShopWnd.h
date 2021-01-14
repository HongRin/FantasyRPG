#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "MercenaryShopWnd.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryShopWnd : public UDraggableWnd
{
	GENERATED_BODY()
		


public:
	UMercenaryShopWnd(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;
};
