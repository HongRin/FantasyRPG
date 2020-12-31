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
	// �θ� ����
	class UInventoryWnd* InventoryWnd;

	class UItemDetailWnd* ItemDetailWnd;

	class UImage* Image_ItemSprite;

	// �κ��丮 ���� �ε���
	int32 InventorySlotIndex;

public:
	UItemSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	// �ش� ������ ���콺 Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/// - InGeometry : ������ ��ġ, ũ�⸦ ��Ÿ���ϴ�.
	/// - InMouseEvent : �Է� �̺�Ʈ�� ����

	// �ش� ������ ���콺 Ŭ�� �Է��� ���� ��� ȣ��˴ϴ�.
	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;
	/// - OutOperation : ��¿� �Ű� �����̸�, ������ �巡�� �۾� ��ü�� ��ȯ�ؾ� �մϴ�.

	// �巡���� �巡�� ��ҵǴ� ȣ�� �Ǵ� �޼���
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// ���콺�� ������ ������ ��� ȣ��Ǵ� �޼���
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// ���콺�� ������ ������ �� ȣ��Ǵ� �޼���
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

public:
	// ������ ������ �����մϴ�.
	void UpdateItemSlot();

public:
	// �θ� ���� (InventoryWnd) �� �����մϴ�.
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

	// �ش� ������ ��Ÿ���� ������ ������ ����ϴ�.
	FItemSlotInfo GetItemSlotInfo();

	void SetItemSlotInfo(FItemSlotInfo itemInfo);
	
};
		