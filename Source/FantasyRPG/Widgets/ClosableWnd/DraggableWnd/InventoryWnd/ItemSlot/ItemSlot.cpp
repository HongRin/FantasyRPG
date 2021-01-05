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

	// 슬롯이 비어있는지 확인합니다.
	if (GetItemSlotInfo().IsEmpty())
	{
		return retVal;
	}
	// 해당 슬롯이 비어있지 않다면
	else
	{
		// 드래그 앤 드롭 작업을 생성하며, 작업 결과를 반환합니다.
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


	// 드래그 앤 드롭 작업 객체를 생성합니다.
	UItemSlotDragDropOperation* dragDropOp = Cast<UItemSlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(
		UItemSlotDragDropOperation::StaticClass()));

	if (IsValid(dragDropOp))
	{
		// 아이템 이미지를 드래깅 색상으로 설정합니다.
		Image_ItemSprite->SetBrushTintColor(DraggingSlotColor);

		// 피벗을 설정합니다.
		dragDropOp->Pivot = EDragPivot::CenterCenter;

		UUserWidget* DragWidget = CreateWidget<UUserWidget>(this, ItemSlotWidgetClass);

		// 드래그 앤 드랍시 보여질 위젯을 설정합니다.
		Cast<UImage>(DragWidget->GetWidgetFromName(TEXT("Image_DragItem")))->SetBrushFromTexture(
			Cast<UTexture2D>(Image_ItemSprite->Brush.GetResourceObject()));

		// 드래그 앤 드랍시 보여질 위젯을 설정합니다.
		dragDropOp->DefaultDragVisual = DragWidget;

		// 드래깅을 시작한 슬롯을 설정합니다.
		dragDropOp->DraggingSlot = this;
	}

	// 출력용 매개 변수에 드래그 앤 드롭 작업 객체를 설정합니다.
	OutOperation = dragDropOp;
}

void UItemSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	// 아이템 이미지를 기본 색상으로 설정합니다.
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
	
		// 개수 텍스트 설정
		Text_ItemCount->SetText(FText::FromString(
			(itemSlotInfo.ItemCount == 1) ? TEXT("") : FString::FromInt(itemSlotInfo.ItemCount)
		));

		UFRGameInstance* gameInst = Cast<UFRGameInstance>(GetGameInstance());
	
		// 아이템 이미지를 로드합니다.
		UTexture2D* itemImage =
			Cast<UTexture2D>(gameInst->GetStreamableManager()->LoadSynchronous(itemInfo->ItemSpritePath));
	
		// 이미지를 설정합니다.
		Image_ItemSprite->SetBrushFromTexture(itemImage);
	
		// 기본 색상으로 변경합니다.
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
