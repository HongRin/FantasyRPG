#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "ItemDetailWnd.generated.h"

UCLASS()
class FANTASYRPG_API UItemDetailWnd : public UClosableWnd
{
	GENERATED_BODY()
	
private:
	class UImage* Image_ItemSprite;
	class UTextBlock* Text_ItemName;
	class UTextBlock* Text_ItemRatingType;
	class UTextBlock* Text_ItemType;
	class UTextBlock* Text_ItemDescription;

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateDetailWnd(class UDataTable* dt_ItemInfo, FName itemCode);
};
