#include "DropItemList.h"

#include "Engine/DataTable.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/InteractableActor/DropItem/DropItem.h"

#include "Components/PlayerInventory/PlayerInventoryComponent.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Structures/ItemInfo/ItemInfo.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"

#include "Widgets/ClosableWnd/DraggableWnd/DropItemWnd/ItemDropWnd.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "TimerManager.h"

UDropItemList::UDropItemList(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEMINFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEMINFO.Succeeded()) DT_ItemInfo = DT_ITEMINFO.Object;
	else { UE_LOG(LogTemp, Error, TEXT("UDropItemList.cpp :: %d LINE :: DT_ITEMINFO is not Loaded!"), __LINE__); }
}

void UDropItemList::NativeConstruct()
{
	Super::NativeConstruct();

	Image_SlotBackground = Cast<UImage>(GetWidgetFromName(TEXT("Image_SlotBackground")));
	Image_ItemSprite = Cast<UImage>(GetWidgetFromName(TEXT("Image_ItemSprite")));
	Text_ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemCount")));
	Text_ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemName")));
	Button_SlotClickEvent = Cast<UButton>(GetWidgetFromName(TEXT("Button_SlotClickEvent")));
	Border_SlotClickEvent = Cast<UBorder>(GetWidgetFromName(TEXT("Border_SlotClickEvent")));

	Border_SlotClickEvent->OnMouseDoubleClickEvent.BindDynamic(this, &UDropItemList::ItemDrop);

	
}

FEventReply UDropItemList::ItemDrop(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	FEventReply Reply;

	UPlayerInventoryComponent* playerInventory = Cast<APlayerCharacter>(GetManager(UPlayerManager)->
		GetPlayerController()->GetPawn())->GetPlayerInventory();


	TArray<FItemSlotInfo> iteminfo = ItemDropWnd->GetDropItems();

	for (int32 i = 0; i < iteminfo.Num(); ++i)
	{
		if (iteminfo[i].ItemCode == ItemCode && iteminfo[i].ItemCount == ItemCount)
		{
			playerInventory->AddItem(ItemCode, ItemCount);
			RemoveFromParent();

			ItemDropWnd->DropItemEmpty(i);
			ItemDropWnd->GetDropItemInstance()->ItemEmpty(i);
		}
	}

	return Reply;
}

void UDropItemList::InitializeDropItem(FName itemCode, int32 itemCount)
{
	ItemCode = itemCode;

	ItemCount = itemCount;

	if (ItemCode == FName(TEXT("")) && ItemCount == 0)
	{
		Image_SlotBackground->SetBrushFromTexture(nullptr);
		Image_SlotBackground->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
		Image_ItemSprite->SetBrushFromTexture(nullptr);
		Image_ItemSprite->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
		Text_ItemCount->SetText(FText::FromString(TEXT("")));
		Text_ItemName->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		FString contextString;
		FItemInfo* itemInfo = DT_ItemInfo->FindRow<FItemInfo>(itemCode, contextString);

		UTexture2D* itemImage = Cast<UFRGameInstance>(GetGameInstance())->
			GetStreamableManager()->LoadSynchronous<UTexture2D>(itemInfo->ItemSpritePath);

		Image_ItemSprite->SetBrushFromTexture(itemImage);
		Text_ItemCount->SetText(FText::FromString((ItemCount == 1) ? TEXT("") : FString::FromInt(itemCount)));

		switch (itemInfo->ItemRatingType)
		{
		case EItemRatingType::RT_NORMAL:
			Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
			break;
		case EItemRatingType::RT_RARE:
			Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(0.18f, 0.08f, 1.0f, 1.0f)));
			break;
		case EItemRatingType::RT_UNIQUE:
			Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.04f, 1.0f, 1.0f)));
			break;
		case EItemRatingType::RT_EPIC:
			Text_ItemName->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.3f, 0.0f, 1.0f)));
			break;
		}

		Text_ItemName->SetText(itemInfo->ItemName);
	}
}
