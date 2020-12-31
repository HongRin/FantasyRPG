#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Enums/ShopItemType.h"
#include "TradeWnd.generated.h"

DECLARE_DELEGATE_OneParam(FOnOkButtonClickSignature, int32)

UCLASS()
class FANTASYRPG_API UTradeWnd : public UDraggableWnd
{
	GENERATED_BODY()

public:
	FOnOkButtonClickSignature OnOkButtonClickEvent;

private:

	EShopItemType ItemType;

	int32 Price;
	// 최대 교환 가능 아이템 개수를 나타냅니다.
	int32 MaxTradeCount;

	int32 TradeCount;

	struct FItemInfo* ItemInfo;

	class UTextBlock* Text_ItemName;
	class UTextBlock* Text_Q;
	class UEditableTextBox* EditableTextBox_TradeCount;
	class UTextBlock* Text_Costs;
	class UButton* Button_Cancel;
	class UButton* Button_Ok;
	class UButton* Button_Plus;
	class UButton* Button_Minus;

protected:
	virtual void NativeConstruct() override;

public:
	void InitializeTradeWnd(EShopItemType itemType,
		struct FItemInfo* itemInfo, int32 costs, int32 maxTradeCount = 0);

private:
	UFUNCTION()
		void OnTradeCountChanged(const FText& text);

	UFUNCTION()
		void OnOkButtonClicked();

	UFUNCTION()
		void OnPlusButtonClicked();


	UFUNCTION()
		void OnMinusButtonClicked();

};

