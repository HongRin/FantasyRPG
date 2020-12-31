#include "SaleItem.h"

#include "Engine/Texture2D.h"

#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/ShopWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/TradeWnd/TradeWnd.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"


#include "Components/PlayerInventory/PlayerInventoryComponent.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

void USaleItem::NativeConstruct()
{
	Super::NativeConstruct();

	Image_ItemSprite = Cast<UImage>(GetWidgetFromName(TEXT("Image_ItemSprite")));
	Text_ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemCount")));
	Text_ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemName")));
	Text_Costs = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Costs")));
	Text_SaleOrBuy = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SaleOrBuy")));
	Button_SaleOrBuy = Cast<UButton>(GetWidgetFromName(TEXT("Button_SaleOrBuy")));

	Button_SaleOrBuy->OnClicked.AddDynamic(this, &USaleItem::OnSaleOrBuyButtonClicked);

}

void USaleItem::InitializeSaleItem(EShopItemType shopItemType, FItemInfo itemInfo,
	UTexture2D* itemImage, int32 itemCount, FText itemName, int32 costs, int32 inventoryItemIndex)
{
	InventoryItemIndex = inventoryItemIndex;

	// 아이템 정보 설정
	ItemInfo = itemInfo;

	// 상점 아이템 타입 설정
	ShopItemType = shopItemType;

	// 상점 아이템 가격 설정
	ItemPrice = costs;

	InventoryItemCount = itemCount;

	// 아이템 이미지 설정
	Image_ItemSprite->SetBrushFromTexture(itemImage);

	// 아이템 개수 설정
	Text_ItemCount->SetText(FText::FromString(
		(itemCount == 1 ? TEXT("") : FString::FromInt(itemCount))
	));

	// 아이템 이름 설정
	Text_ItemName->SetText(itemName);

	// 아이템 가격 설정
	Text_Costs->SetText(FText::FromString(FString::FromInt(costs)));

	// 버튼 텍스트 설정
	Text_SaleOrBuy->SetText(FText::FromString(
		(shopItemType == EShopItemType::SI_InventoryItem ? TEXT("판매") : TEXT("구매"))
	));
}

void USaleItem::OnSaleOrBuyButtonClicked()
{
	auto tradeWnd = ShopWnd->CreateTradeWnd(this ,ShopItemType, &ItemInfo, ItemPrice);

	if (!IsValid(tradeWnd)) return;

	tradeWnd->OnOkButtonClickEvent.BindLambda([this](int32 itemCount)
		{
			Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn())->
				GetPlayerInventory()->AddItem(ItemInfo.ItemCode, itemCount);
		});
}
