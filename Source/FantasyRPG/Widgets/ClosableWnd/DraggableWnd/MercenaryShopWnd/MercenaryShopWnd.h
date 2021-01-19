#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Structures/ShopItemInfo/ShopItemInfo.h"
#include "MercenaryShopWnd.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryShopWnd : public UDraggableWnd
{
	GENERATED_BODY()
		
private :
	class UDataTable* DT_MercenaryInfo;
	TSubclassOf<class UMercenaryRow> BP_MercenaryRow;

	class UScrollBox* ScrollBox_MercenaryList;
	class UMercenaryStateComponent* MercenaryState;
public:
	UMercenaryShopWnd(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;

public :
	void InitializeMercenaryShopWnd(TArray<FShopItemInfo> saleItems);
};
