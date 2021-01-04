#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"
#include "ItemDropWnd.generated.h"

UCLASS()
class FANTASYRPG_API UItemDropWnd : public UDraggableWnd
{
	GENERATED_BODY()

private:
	class TSubclassOf<class UDropItemList> DropItemListClass;

private:
	TArray<FItemSlotInfo> Items;
	class ADropItem* DropItemInstance;

private:
	class UGridPanel* GridPanel_DropItemList;
	class UButton* Button_Cancel;
	class UButton* Button_AllDrop;

public:
	UItemDropWnd(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	// 얻을 수 있는 아이템 정보를 초기화합니다.
	void InitializeRootItems(TArray<FItemSlotInfo> items);

	FORCEINLINE void SetDropItem(class ADropItem* dropItemInstance)
	{
		DropItemInstance = dropItemInstance;
	}

	FORCEINLINE const TArray<FItemSlotInfo>& GetDropItems() const
	{ return Items; }

	FORCEINLINE class ADropItem* GetDropItemInstance() const
	{ return DropItemInstance; }

	FORCEINLINE void DropItemEmpty(int32 index)
	{
		Items[index] = FItemSlotInfo();
	}

private:
	UFUNCTION()
		void ItemAllDrop();
	
};
