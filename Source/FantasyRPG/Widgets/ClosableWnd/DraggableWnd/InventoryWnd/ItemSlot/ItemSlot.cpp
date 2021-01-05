#include "ItemSlot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/InventoryWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/ItemDetailWnd/ItemDetailWnd.h"
#include "ItemSlotDragDropOperation.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ClosableWndController/ClosableWndControllerComponent.h"
#include "Components/PlayerInventory/PlayerInventoryComponent.h"

#include "Structures/ItemInfo/ItemInfo.h"

#include "Single/GameInstance/FRGameInstance.h"

#include "Engine/DataTable.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

UItemSlot::UItemSlot(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_ITEM_SLOT(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/InventoryWnd/BP_DragItemImage.BP_DragItemImage_C'"));
	
	if (BP_ITEM_SLOT.Succeeded())
		ItemSlotWidgetClass = BP_ITEM_SLOT.Class;

	static ConstructorHelpers::FClassFinder<UItemDetailWnd> BP_ITEM_DETAIL_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/InventoryWnd/BP_ItemDetailWnd.BP_ItemDetailWnd_C'"));
	if (BP_ITEM_DETAIL_WND.Succeeded())
		ItemDetailWndClass = BP_ITEM_DETAIL_WND.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_ItemInfo.DT_ItemInfo'"));

	if (DT_ITEM_INFO.Succeeded())
		DT_ItemInfo = DT_ITEM_INFO.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T_EMPTY_TEXTURE(
		TEXT("Texture2D'/Game/Resources/UIImage/ItemImage/empty.empty'"));
	if (T_EMPTY_TEXTURE.Succeeded()) EmptyTexture = T_EMPTY_TEXTURE.Object;

	NormalSlotColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	DraggingSlotColor = FLinearColor(0.15f, 0.15f, 0.15f, 1.0f);
}

void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Image_ItemSprite = Cast<UImage>(GetWidgetFromName(TEXT("Image_ItemSprite")));
	Text_ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ItemCount")));
}

FReply UItemSlot::NativeOnMouseButtonDown(
	const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply retVal = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// ������ ����ִ��� Ȯ���մϴ�.
	if (GetItemSlotInfo().IsEmpty())
	{
		return retVal;
	}
	// �ش� ������ ������� �ʴٸ�
	else
	{
		// �巡�� �� ��� �۾��� �����ϸ�, �۾� ����� ��ȯ�մϴ�.
		return UWidgetBlueprintLibrary::DetectDragIfPressed(
			InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
}

void UItemSlot::NativeOnDragDetected(
	const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);


	// �巡�� �� ��� �۾� ��ü�� �����մϴ�.
	UItemSlotDragDropOperation* dragDropOp = Cast<UItemSlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(
		UItemSlotDragDropOperation::StaticClass()));

	if (IsValid(dragDropOp))
	{
		// ������ �̹����� �巡�� �������� �����մϴ�.
		Image_ItemSprite->SetBrushTintColor(DraggingSlotColor);

		// �ǹ��� �����մϴ�.
		dragDropOp->Pivot = EDragPivot::CenterCenter;

		UUserWidget* DragWidget = CreateWidget<UUserWidget>(this, ItemSlotWidgetClass);

		// �巡�� �� ����� ������ ������ �����մϴ�.
		Cast<UImage>(DragWidget->GetWidgetFromName(TEXT("Image_DragItem")))->SetBrushFromTexture(
			Cast<UTexture2D>(Image_ItemSprite->Brush.GetResourceObject()));

		// �巡�� �� ����� ������ ������ �����մϴ�.
		dragDropOp->DefaultDragVisual = DragWidget;

		// �巡���� ������ ������ �����մϴ�.
		dragDropOp->DraggingSlot = this;
	}

	// ��¿� �Ű� ������ �巡�� �� ��� �۾� ��ü�� �����մϴ�.
	OutOperation = dragDropOp;
}

void UItemSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	// ������ �̹����� �⺻ �������� �����մϴ�.
	Image_ItemSprite->SetBrushTintColor(NormalSlotColor);
}

bool UItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool retVal = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemSlotDragDropOperation* dragDropOp = Cast<UItemSlotDragDropOperation>(InOperation);
	UPlayerInventoryComponent* playerInventory = InventoryWnd->GetPlayerInventoryComponent();

	playerInventory->SwapItem(dragDropOp->DraggingSlot, this);

	return retVal;
}

void UItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (GetItemSlotInfo().IsEmpty()) return;

	if (!IsValid(ItemDetailWnd))
	{
		ItemDetailWnd = Cast<UItemDetailWnd>(InventoryWnd->CreateChildClosableWnd(ItemDetailWndClass));

		ItemDetailWnd->UpdateDetailWnd(DT_ItemInfo, GetItemSlotInfo().ItemCode);

		Cast<UCanvasPanelSlot>(ItemDetailWnd->Slot)->SetPosition(InGeometry.GetAbsolutePosition() + (InGeometry.GetAbsoluteSize() * 0.5f));
	}
}

void UItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (IsValid(ItemDetailWnd))
	{
		(InventoryWnd->GetPlayerInventoryComponent()->GetClosableWndController())->CloseWnd(false, ItemDetailWnd);
		ItemDetailWnd = nullptr;
	}
}

void UItemSlot::UpdateItemSlot()
{
	FItemSlotInfo itemSlotInfo = GetItemSlotInfo();
	
	if (itemSlotInfo.IsEmpty())
	{
		Image_ItemSprite->SetBrushFromTexture(EmptyTexture);
		Text_ItemCount->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		FString contextString;
		FItemInfo* itemInfo = DT_ItemInfo->FindRow<FItemInfo>(
			itemSlotInfo.ItemCode, contextString);
	
		// ���� �ؽ�Ʈ ����
		Text_ItemCount->SetText(FText::FromString(
			(itemSlotInfo.ItemCount == 1) ? TEXT("") : FString::FromInt(itemSlotInfo.ItemCount)
		));

		UFRGameInstance* gameInst = Cast<UFRGameInstance>(GetGameInstance());
	
		// ������ �̹����� �ε��մϴ�.
		UTexture2D* itemImage =
			Cast<UTexture2D>(gameInst->GetStreamableManager()->LoadSynchronous(itemInfo->ItemSpritePath));
	
		// �̹����� �����մϴ�.
		Image_ItemSprite->SetBrushFromTexture(itemImage);
	
		// �⺻ �������� �����մϴ�.
		Image_ItemSprite->SetBrushTintColor(NormalSlotColor);
	}
}

FItemSlotInfo UItemSlot::GetItemSlotInfo()
{
	FItemSlotInfo slotInfo = InventoryWnd->GetPlayerInventoryComponent()->GetInventoryItems()[InventorySlotIndex];

	return slotInfo;
}

void UItemSlot::SetItemSlotInfo(FItemSlotInfo itemInfo)
{
	InventoryWnd->GetPlayerInventoryComponent()->SetItemSlotInfo(InventorySlotIndex, itemInfo);
}
