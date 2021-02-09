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
	// ���� ������ �����մϴ�.
	UItemSlot* newItemSlot = CreateWidget<UItemSlot>(this, BP_ItemSlotClass);

	// ������ ���� ������ GridPanel �� �ڽ� �������� �߰��մϴ�.
	GridPanel_Content->AddChild(newItemSlot);

	newItemSlot->SetInventorySlotIndex(InventorySlots.Num());

	// ������ ��ġ�� �����մϴ�.
	{
		int32 colum = newItemSlot->GetInventorySlotIndex() % 7;
		int32 row = newItemSlot->GetInventorySlotIndex() / 7;

		newItemSlot->GetGridSlot()->SetColumn(colum);
		newItemSlot->GetGridSlot()->SetRow(row);

		newItemSlot->SetInvenotryWnd(this);
	}

	// �迭�� �߰��մϴ�.
	InventorySlots.Add(newItemSlot);
}

void UInventoryWnd::InitializeInventoryWnd(class UPlayerInventoryComponent* playerInventory)
{
	PlayerInventory = playerInventory;

	// ���� ����
	for (int i = 0; i < PlayerInfo->InventorySlotConut; i++)
		CreateSlot();

	// ���� ����
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
