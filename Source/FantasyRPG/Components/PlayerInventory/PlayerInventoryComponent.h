#pragma once

#include "FantasyRPG.h"
#include "Components/ActorComponent.h"
#include "Enums/EquipItemType.h"
#include "Enums/ReinforceResult.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"
#include "PlayerInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventorySlotChangedSignature)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASYRPG_API UPlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 인벤토리 슬롯에 변경이 있을 경우 호출될 대리자
	FOnInventorySlotChangedSignature OnInventorySlotChanged;

private :
	TMap<EEquipItemType, FName> EquipItems;

	class UDataTable* DTEquipItemInfo;

	class UDataTable* DTItemInfo;

	struct FPlayerInfo* PlayerInfo;

	// 닫을 수 있는 창을 관리하는 객체를 나타냅니다.
	class UClosableWndControllerComponent* ClosableWndController;

	// 소지중인 아이템들을 나타냅니다.
	TArray<FItemSlotInfo> InventoryItems;

public:	
	UPlayerInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	void InitializeEquipItems();

	// 인벤토리 아이템을 초기화합니다.
	void InitializeInventoryItems();

public :
	void UpdateEquipItemState(EEquipItemType equipitemType);

	EReinforceResult TryReinforce(EEquipItemType itemType);


	// 인벤토리 아이템을 교체합니다.
	void SwapItem(class UItemSlot* firstItemSlot, class UItemSlot* SecondItemSlot);

	bool AddItem(FName itemCode, int32 itemCount = 1);

	bool RemoveItem(int32 slotIndex, int32 removeCount);

	// 아이템이 담긴 슬롯 인덱스를 반환합니다.
	int32 GetItemIndex(FItemSlotInfo itemSlotInfo);

public :
	FORCEINLINE FName GetEquipItemCode(EEquipItemType equipType) const
	{ return EquipItems[equipType]; }

	// 인벤토리 아이템을 설정합니다.
	FORCEINLINE void SetItemSlotInfo(int32 slotIndex, FItemSlotInfo slotInfo)
	{ InventoryItems[slotIndex] = slotInfo; }

	FORCEINLINE const TArray<FItemSlotInfo>& GetInventoryItems() const
	{ return InventoryItems; }

	FORCEINLINE class UClosableWndControllerComponent* GetClosableWndController() const
	{ return ClosableWndController; }

};
