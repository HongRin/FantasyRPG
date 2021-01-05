#include "PlayerInventoryComponent.h"
#include "Engine/DataTable.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"

#include "Structures/EquipItem/EquipItemInfo.h"
#include "Structures/ItemInfo/ItemInfo.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/InventoryWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemSlot/ItemSlot.h"

UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EQUIP_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_EquipItemInfo.DT_EquipItemInfo'"));
	if (DT_EQUIP_ITEM_INFO.Succeeded()) DTEquipItemInfo = DT_EQUIP_ITEM_INFO.Object;
	else { UE_LOG(LogTemp, Error, TEXT("PlayerInventoryComponent.cpp :: %d LINE :: DT_EQUIP_ITEM_INFO is not loaded!"), __LINE__); }

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DTItemInfo = DT_ITEM_INFO.Object;
	else { UE_LOG(LogTemp, Error, TEXT("PlayerInventoryComponent.cpp :: %d LINE :: DT_ITEM_INFO is not loaded!"), __LINE__); }
}


void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeEquipItems();
	InitializeInventoryItems();

	ClosableWndController = (GetManager(UPlayerManager)->GetPlayerController())->GetClosableWndControllerComponent();
}


void UPlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerInventoryComponent::InitializeEquipItems()
{
	EquipItems.Empty();
	EquipItems.Add(EEquipItemType::EI_Weapon, TEXT("10000"));
	EquipItems.Add(EEquipItemType::EI_Armor,  TEXT("20000"));
}

void UPlayerInventoryComponent::InitializeInventoryItems()
{
	UPlayerManager* playerManager = GetManager(UPlayerManager);
	FPlayerInfo* playerInfo = playerManager->GetPlayerInfo();

	for (int i = 0; i < playerInfo->InventorySlotConut; ++i)
		InventoryItems.Add(FItemSlotInfo());

	// -- TEST CODE --
	AddItem(FName(TEXT("40001")), 11);
	AddItem(FName(TEXT("40002")), 12);
	AddItem(FName(TEXT("50001")), 1);
	AddItem(FName(TEXT("50002")), 1);
	AddItem(FName(TEXT("50003")), 1);
	AddItem(FName(TEXT("50004")), 1);

	RemoveItem(0, 1);
	RemoveItem(1, 2);
}

void UPlayerInventoryComponent::UpdateEquipItemState(EEquipItemType equipitemType)
{
	// �������� ������ �ڵ带 �����մϴ�.
	FName itemCode = EquipItems[equipitemType];

	// ������ �ڵ带 �̿��Ͽ� ������ ������ ����ϴ�.
	FString contextString;
	FEquipItemInfo* equipItemInfo = DTEquipItemInfo->FindRow<FEquipItemInfo>(
		itemCode, contextString);

	UPlayerManager* playerManger = GetManager(UPlayerManager);
	PlayerInfo = playerManger->GetPlayerInfo();
	
	PlayerInfo->Atk += equipItemInfo->AdditionalOffensiveForce;
	PlayerInfo->MaxHp += equipItemInfo->AdditionalHp;
}

EReinforceResult UPlayerInventoryComponent::TryReinforce(EEquipItemType itemType)
{
	FString contextString;
	auto equipItemInfo = DTEquipItemInfo->FindRow<FEquipItemInfo>(GetEquipItemCode(itemType), contextString);

	auto nextEquipItemInfo = DTEquipItemInfo->FindRow<FEquipItemInfo>(equipItemInfo->NextReinforcementItemCode, contextString);

	// ��ȭ�� �����ߴٸ�
	if (nextEquipItemInfo->ReinforcementProbability >= FMath::RandRange(1.0f, 100.0f))
	{
		EquipItems[itemType] = nextEquipItemInfo->ItemCode;

		return EReinforceResult::RF_Success;
	}

	return EReinforceResult::RF_Fail;
}

void UPlayerInventoryComponent::SwapItem(UItemSlot* firstItemSlot, UItemSlot* SecondItemSlot)
{
	auto tempItemInfo = firstItemSlot->GetItemSlotInfo();
	firstItemSlot->SetItemSlotInfo(SecondItemSlot->GetItemSlotInfo());
	SecondItemSlot->SetItemSlotInfo(tempItemInfo);

	firstItemSlot->UpdateItemSlot();
	SecondItemSlot->UpdateItemSlot();
}

bool UPlayerInventoryComponent::AddItem(FName itemCode, int32 itemCount)
{
	// �߰��Ϸ��� ������ ������ �����մϴ�.
	FString contextString;
	FItemInfo* itemInfo = DTItemInfo->FindRow<FItemInfo>(itemCode, contextString);

	// �߰��Ϸ��� �����۰� ������ �������� ��� ���� �ε����� ������ ����
	int32 slotIndex = INDEX_NONE;

	// ���ο� �������� ������ �� �ִ� �� ���� �ε����� ����Ȱ ����
	int32 emptySlotIndex = INDEX_NONE;

	// �迭���� ������ ������ ���԰� �� ������ Ž���մϴ�.
	for (int32 i = 0; i < InventoryItems.Num(); ++i)
	{
		// �߰��Ϸ��� �����۰� ������ �������� �����Ѵٸ�
		if (InventoryItems[i].ItemCode == itemCode)
		{
			if ((InventoryItems[i].ItemCount + itemCount) <= itemInfo->MaxCount)
			{
				slotIndex = i;

				// �߰��� �� �ִ� ���� �ε����� ã�����Ƿ�, Ž���� ����
				break;
			}
		}

		// �� ������ ã�Ҵٸ�
		if (emptySlotIndex == INDEX_NONE && InventoryItems[i].IsEmpty())
		{
			// �� ���� �ε��� ����
			emptySlotIndex = i;
		}
	}

	// �������� �߰��� �� �ִ� ������ �������� �ʴ´ٸ�
	if (slotIndex == INDEX_NONE && emptySlotIndex == INDEX_NONE)
		// ������ �߰� ����
		return false;

	// ������ �������� ���� ������ �����Ѵٸ�
	if (slotIndex != INDEX_NONE)
	{
		// ã�� ������ ������ ������ ������ŵ�ϴ�.
		InventoryItems[slotIndex].AddItemCount(itemCount);
	}

	// ������ �������� ���� ������ �������� ������, �� ������ ã�Ҵٸ�
	else if (emptySlotIndex != INDEX_NONE)
	{
		// ã�� ���Կ� �������� �߰��մϴ�.
		InventoryItems[emptySlotIndex] = FItemSlotInfo(itemCode, itemCount);
	}

	if (OnInventorySlotChanged.IsBound())
		OnInventorySlotChanged.Broadcast();

	// ������ �߰� ����
	return true;
}

bool UPlayerInventoryComponent::RemoveItem(int32 slotIndex, int32 removeCount)
{
	// slotIndex �� InventoryItems �迭 ������ �ʰ��Ѵٸ�
	if (InventoryItems.Num() <= slotIndex)

		// ���� ����
		return false;

	// ������ ������ ����ִٸ�
	if (InventoryItems[slotIndex].IsEmpty())

		// ���� ����
		return false;

	// ������ ���� ����
	InventoryItems[slotIndex].ItemCount -= removeCount;

	// ���� �������� ������ 0 ���϶�� ������ ���ϴ�.
	if (InventoryItems[slotIndex].ItemCount <= 0)
		InventoryItems[slotIndex] = FItemSlotInfo();

	if (OnInventorySlotChanged.IsBound())
		OnInventorySlotChanged.Broadcast();

	return true;
}

int32 UPlayerInventoryComponent::GetItemIndex(FItemSlotInfo itemSlotInfo)
{
	return InventoryItems.Find(itemSlotInfo);
}
