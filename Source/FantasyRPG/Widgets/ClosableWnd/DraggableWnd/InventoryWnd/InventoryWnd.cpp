#include "InventoryWnd.h"

#include "Components/PlayerInventory/PlayerInventoryComponent.h"
#include "Components/GridPanel.h"

#include "Structures/Player/PlayerInfo.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/ItemSlot.h"



UInventoryWnd::UInventoryWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FClassFinder<UItemSlot> BP_ITEM_SLOT(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/InventoryWnd/BP_ItemSlot.BP_ItemSlot_C'"));
	if (BP_ITEM_SLOT.Succeeded()) BP_ItemSlotClass = BP_ITEM_SLOT.Class;
}

void UInventoryWnd::NativeConstruct()
{
	Super::NativeConstruct();

	UPlayerManager* playerManager = GetManager(UPlayerManager);
	PlayerInfo = playerManager->GetPlayerInfo();

	GridPanel_Content = Cast<UGridPanel>(GetWidgetFromName(TEXT("GridPanel_Content")));

	UpdateWndSize(448.0f, 600.0f);

}

void UInventoryWnd::CreateSlot()
{
	// 슬롯 위젯을 생성합니다.
	UItemSlot* newItemSlot = CreateWidget<UItemSlot>(this, BP_ItemSlotClass);

	// 생성한 슬롯 위젯을 GridPanel 의 자식 위젯으로 추가합니다.
	GridPanel_Content->AddChild(newItemSlot);

	newItemSlot->SetInventorySlotIndex(InventorySlots.Num());

	// 슬롯의 위치를 설정합니다.
	{
		int32 colum = newItemSlot->GetInventorySlotIndex() % 7;
		int32 row = newItemSlot->GetInventorySlotIndex() / 7;

		newItemSlot->GetGridSlot()->SetColumn(colum);
		newItemSlot->GetGridSlot()->SetRow(row);

		newItemSlot->SetInvenotryWnd(this);
	}

	// 배열에 추가합니다.
	InventorySlots.Add(newItemSlot);
}

void UInventoryWnd::InitializeInventoryWnd(class UPlayerInventoryComponent* playerInventory)
{
	PlayerInventory = playerInventory;

	// 슬롯 생성
	for (int i = 0; i < PlayerInfo->InventorySlotConut; i++)
		CreateSlot();

	// 슬롯 갱신
	UpdateInventorySlots();

	auto hDelegate = PlayerInventory->OnInventorySlotChanged.AddUObject(this, &UInventoryWnd::UpdateInventorySlots);
	onWndClosed.AddLambda([=]() {PlayerInventory->OnInventorySlotChanged.Remove(hDelegate); });
}

void UInventoryWnd::UpdateInventorySlots()
{
	for (auto slot : InventorySlots)
		slot->UpdateItemSlot();
	
	int32 value = 1;

	switch (value)
	{
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("value :: %d"), value);
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("value :: %d"), value);
		break;
	}
}
