#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"

#include "Components/GridSlot.h"

#include "Structures/ItemSlotInfo/ItemSlotInfo.h"

#include "ItemSlot.generated.h"

UCLASS()
class FANTASYRPG_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

private:
	TSubclassOf<UUserWidget> ItemSlotWidgetClass;

	TSubclassOf<class UItemDetailWnd> ItemDetailWndClass;
	
	class UDataTable* DT_ItemInfo;

	class UTexture2D* EmptyTexture;

	class UTextBlock* Text_ItemCount;

	class UButton* Button_LeftClick;

	FLinearColor NormalSlotColor;
	FLinearColor DraggingSlotColor;

private:
	// 부모 위젯
	class UInventoryWnd* InventoryWnd;

	class UItemDetailWnd* ItemDetailWnd;

	class UImage* Image_ItemSprite;

	// 인벤토리 슬롯 인덱스
	int32 InventorySlotIndex;

public:
	UItemSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	// 해당 위젯에 마우스 클릭 입력이 있을 경우 호출됩니다.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/// - InGeometry : 위젯의 위치, 크기를 나타냅니다.
	/// - InMouseEvent : 입력 이벤트의 종류

	// 해당 위젯에 마우스 클릭 입력이 있을 경우 호출됩니다.
	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;
	/// - OutOperation : 출력용 매개 변수이며, 감지된 드래그 작업 객체를 반환해야 합니다.

	// 드래그중 드래그 취소되는 호출 되는 메서드
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// 마우스와 위젯이 겹쳤을 경우 호출되는 메서드
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// 마우스와 위젯이 끝났을 때 호출되는 메서드
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

public:
	// 아이템 슬롯을 갱신합니다.
	void UpdateItemSlot();

public:
	// 부모 위젯 (InventoryWnd) 를 설정합니다.
	FORCEINLINE void SetInvenotryWnd(class UInventoryWnd* inventoryWnd)
	{
		InventoryWnd = inventoryWnd;
	}

	FORCEINLINE void SetInventorySlotIndex(int32 index)
	{
		InventorySlotIndex = index;
	}

	FORCEINLINE int32 GetInventorySlotIndex() const
	{
		return InventorySlotIndex;
	}

	FORCEINLINE class UGridSlot* GetGridSlot() const
	{
		return Cast<UGridSlot>(Slot);
	}

	// 해당 슬롯이 나타내는 아이템 정보를 얻습니다.
	FItemSlotInfo GetItemSlotInfo();

	void SetItemSlotInfo(FItemSlotInfo itemInfo);
	
};
		