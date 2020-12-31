#include "ItemDetailWnd.h"

#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Structures/ItemInfo/ItemInfo.h"

#include "Single/GameInstance/FRGameInstance.h"

#include "Engine/DataTable.h"

void UItemDetailWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Image_ItemSprite = Cast<UImage>(GetWidgetFromName(TEXT("Image_ItemSprite")));
	Text_ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemName")));
	Text_ItemRatingType = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemRatingType")));
	Text_ItemType = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemType")));
	Text_ItemDescription = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemDescription")));

	SetVisibility(ESlateVisibility::HitTestInvisible);

	UpdateWndSize(400.0f, 600.0f);
}

void UItemDetailWnd::UpdateDetailWnd(UDataTable* dt_ItemInfo, FName itemCode)
{
	FString contextString;
	FItemInfo* itemInfo = dt_ItemInfo->FindRow<FItemInfo>(
		itemCode, contextString);

	UFRGameInstance* gameInst = Cast<UFRGameInstance>(GetGameInstance());

	// 아이템 이미지를 로드합니다.
	UTexture2D* itemImage =
		Cast<UTexture2D>(gameInst->GetStreamableManager()->LoadSynchronous(itemInfo->ItemSpritePath));


	switch (itemInfo->ItemRatingType)
	{
	case EItemRatingType::RT_NORMAL :
		Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
		Text_ItemRatingType->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
		Text_ItemRatingType->SetText(FText::FromString(TEXT("노멀 아이템")));
		break;
	case EItemRatingType::RT_RARE:
		Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(0.18f, 0.08f, 1.0f, 1.0f)));
		Text_ItemRatingType->SetColorAndOpacity(FSlateColor(FLinearColor(0.18f, 0.08f, 1.0f, 1.0f)));
		Text_ItemRatingType->SetText(FText::FromString(TEXT("레어 아이템")));
		break;
	case EItemRatingType::RT_UNIQUE:
		Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.04f, 1.0f, 1.0f)));
		Text_ItemRatingType->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.04f, 1.0f, 1.0f)));
		Text_ItemRatingType->SetText(FText::FromString(TEXT("유니크 아이템")));
		break;
	case EItemRatingType::RT_EPIC:
		Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.3f, 0.0f, 1.0f)));
		Text_ItemRatingType->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.3f, 0.0f, 1.0f)));
		Text_ItemRatingType->SetText(FText::FromString(TEXT("에픽 아이템")));
		break;

	}

	Text_ItemName->SetText(itemInfo->ItemName);

	Text_ItemDescription->SetText(itemInfo->ItemDescriptin);
	Image_ItemSprite->SetBrushFromTexture(itemImage);

	switch (itemInfo->ItemType)
	{
	case EItemType::IT_Consumption:
		Text_ItemType->SetText(FText::FromString(TEXT("소비 아이템")));
		break;
	case EItemType::IT_EtCetera:
		Text_ItemType->SetText(FText::FromString(TEXT("기타 아이템")));
		break;
	}
}
