#include "ItemDropWnd.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/InteractableActor/DropItem/DropItem.h"

#include "Components/PlayerInventory/PlayerInventoryComponent.h"
#include "Components/GridPanel.h"
#include "Components/Button.h"
#include "Components/GridSlot.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/DropItemWnd/DropItemList/DropItemList.h"

UItemDropWnd::UItemDropWnd(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UDropItemList> BP_DROP_ITEM_LIST(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/ItemDropWnd/BP_DropItemList.BP_DropItemList_C'"));
	if (BP_DROP_ITEM_LIST.Succeeded()) DropItemListClass = BP_DROP_ITEM_LIST.Class;
	else { UE_LOG(LogTemp, Error, TEXT("UItemDropWnd.cpp :: %d LINE :: BP_DROP_ITEM_LIST is not loaded!"), __LINE__); }
}

void UItemDropWnd::NativeConstruct()
{
	Super::NativeConstruct();

	GridPanel_DropItemList = Cast<UGridPanel>(GetWidgetFromName(TEXT("GridPanel_DropItemList")));
	Button_Cancel = Cast<UButton>(GetWidgetFromName(TEXT("Button_Cancel")));
	Button_AllDrop = Cast<UButton>(GetWidgetFromName(TEXT("Button_AllDrop")));

	Button_Cancel->OnClicked.AddDynamic(this, &UClosableWnd::OnCloseButtonClicked);
	Button_AllDrop->OnClicked.AddDynamic(this, &UItemDropWnd::ItemAllDrop);


	UpdateWndSize(500.0f, 400.0f);
}

void UItemDropWnd::InitializeRootItems(TArray<FItemSlotInfo> items)
{
	Items = items;

	for (int32 i = 0; i < items.Num(); ++i)
	{
		UDropItemList* dropItemSlot = CreateWidget<UDropItemList>(this, DropItemListClass);
		GridPanel_DropItemList->AddChild(dropItemSlot);

		UGridSlot* gridSlot = Cast<UGridSlot>(dropItemSlot->Slot);
		gridSlot->SetColumn(i % 2);
		gridSlot->SetRow(i / 2);

		dropItemSlot->InitializeDropItem(items[i].ItemCode, items[i].ItemCount);
	}
}

void UItemDropWnd::ItemAllDrop()
{
	UPlayerInventoryComponent* playerInventory = Cast<APlayerCharacter>(GetManager(UPlayerManager)->
		GetPlayerController()->GetPawn())->GetPlayerInventory();

	// 제거할 아이템 인덱스를 저장할 배열
	TArray<FItemSlotInfo> destroyItemInfo;

	for (int32 i = 0; i < Items.Num(); ++i)
	{
		// 아이템 얻기에 성공했다면
		if (playerInventory->AddItem(Items[i].ItemCode, Items[i].ItemCount))

			// 제거할 아이템 인덱스를 저장합니다.
			destroyItemInfo.Add(Items[i]);

		// 아이템 얻기에 실패했다면 반복 종료
		else break;
	}

	// 제거할 아이템이 존재한다면
	if (destroyItemInfo.Num() != 0)
	{
		// 아이템 제거
		for (int32 i = 0; i < destroyItemInfo.Num(); ++i)
		{
			Items.Remove(destroyItemInfo[i]);
		}
	}

	OnCloseButtonClicked();

	// 얻을 수 있는 아이템이 존재하지 않는다면
	if (Items.Num() == 0)
		DropItemInstance->Destroy();
}
