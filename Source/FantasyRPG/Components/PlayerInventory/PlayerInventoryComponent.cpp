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
	// 장착중인 아이템 코드를 저장합니다.
	FName itemCode = EquipItems[equipitemType];

	// 아이템 코드를 이용하여 아이템 정보를 얻습니다.
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

	// 강화에 성공했다면
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
	// 추가하려는 아이템 정보를 저장합니다.
	FString contextString;
	FItemInfo* itemInfo = DTItemInfo->FindRow<FItemInfo>(itemCode, contextString);

	// 추가하려는 아이템과 동일한 아이템이 담긴 슬롯 인덱스를 저장할 변수
	int32 slotIndex = INDEX_NONE;

	// 새로운 아이템을 저장할 수 있는 빈 슬롯 인덱스를 저장활 변수
	int32 emptySlotIndex = INDEX_NONE;

	// 배열에서 동일한 아이템 슬롯과 빈 슬롯을 탐색합니다.
	for (int32 i = 0; i < InventoryItems.Num(); ++i)
	{
		// 추가하려는 아이템과 동일한 아이템이 존재한다면
		if (InventoryItems[i].ItemCode == itemCode)
		{
			if ((InventoryItems[i].ItemCount + itemCount) <= itemInfo->MaxCount)
			{
				slotIndex = i;

				// 추가할 수 있는 슬롯 인덱스를 찾았으므로, 탐색을 종료
				break;
			}
		}

		// 빈 슬롯을 찾았다면
		if (emptySlotIndex == INDEX_NONE && InventoryItems[i].IsEmpty())
		{
			// 빈 슬롯 인덱스 저장
			emptySlotIndex = i;
		}
	}

	// 아이템을 추가할 수 있는 슬롯이 존재하지 않는다면
	if (slotIndex == INDEX_NONE && emptySlotIndex == INDEX_NONE)
		// 아이템 추가 실패
		return false;

	// 동일한 아이템을 가진 슬롯이 존재한다면
	if (slotIndex != INDEX_NONE)
	{
		// 찾은 슬롯의 아이템 개수를 증가시킵니다.
		InventoryItems[slotIndex].AddItemCount(itemCount);
	}

	// 동일한 아이템을 가진 슬롯은 존재하지 않지만, 빈 슬롯을 찾았다면
	else if (emptySlotIndex != INDEX_NONE)
	{
		// 찾은 슬롯에 아이템을 추가합니다.
		InventoryItems[emptySlotIndex] = FItemSlotInfo(itemCode, itemCount);
	}

	if (OnInventorySlotChanged.IsBound())
		OnInventorySlotChanged.Broadcast();

	// 아이템 추가 성공
	return true;
}

bool UPlayerInventoryComponent::RemoveItem(int32 slotIndex, int32 removeCount)
{
	// slotIndex 가 InventoryItems 배열 범위를 초과한다면
	if (InventoryItems.Num() <= slotIndex)

		// 제거 실패
		return false;

	// 아이템 정보가 비어있다면
	if (InventoryItems[slotIndex].IsEmpty())

		// 제거 실패
		return false;

	// 아이템 개수 감소
	InventoryItems[slotIndex].ItemCount -= removeCount;

	// 만약 아이템의 개수가 0 이하라면 슬롯을 비웁니다.
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
