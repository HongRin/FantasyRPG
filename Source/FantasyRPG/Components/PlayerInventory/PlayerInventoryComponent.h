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
	// �κ��丮 ���Կ� ������ ���� ��� ȣ��� �븮��
	FOnInventorySlotChangedSignature OnInventorySlotChanged;

private :
	TMap<EEquipItemType, FName> EquipItems;

	class UDataTable* DTEquipItemInfo;

	class UDataTable* DTItemInfo;

	struct FPlayerInfo* PlayerInfo;

	// ���� �� �ִ� â�� �����ϴ� ��ü�� ��Ÿ���ϴ�.
	class UClosableWndControllerComponent* ClosableWndController;

	// �������� �����۵��� ��Ÿ���ϴ�.
	TArray<FItemSlotInfo> InventoryItems;

public:	
	UPlayerInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	void InitializeEquipItems();

	// �κ��丮 �������� �ʱ�ȭ�մϴ�.
	void InitializeInventoryItems();

public :
	void UpdateEquipItemState(EEquipItemType equipitemType);

	EReinforceResult TryReinforce(EEquipItemType itemType);


	// �κ��丮 �������� ��ü�մϴ�.
	void SwapItem(class UItemSlot* firstItemSlot, class UItemSlot* SecondItemSlot);

	bool AddItem(FName itemCode, int32 itemCount = 1);

	bool RemoveItem(int32 slotIndex, int32 removeCount);

	// �������� ��� ���� �ε����� ��ȯ�մϴ�.
	int32 GetItemIndex(FItemSlotInfo itemSlotInfo);

public :
	FORCEINLINE FName GetEquipItemCode(EEquipItemType equipType) const
	{ return EquipItems[equipType]; }

	// �κ��丮 �������� �����մϴ�.
	FORCEINLINE void SetItemSlotInfo(int32 slotIndex, FItemSlotInfo slotInfo)
	{ InventoryItems[slotIndex] = slotInfo; }

	FORCEINLINE const TArray<FItemSlotInfo>& GetInventoryItems() const
	{ return InventoryItems; }

	FORCEINLINE class UClosableWndControllerComponent* GetClosableWndController() const
	{ return ClosableWndController; }

};
