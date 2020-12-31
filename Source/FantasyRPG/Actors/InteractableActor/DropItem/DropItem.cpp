#include "DropItem.h"

#include "Engine/Engine.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/FRGameInstance.h"

#include "Widgets/CharacterWidget.h"
#include "Widgets/ClosableWnd/DraggableWnd/DropItemWnd/ItemDropWnd.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"
#include "Components/CharacterWidget/CharacterWidgetComponent.h"

ADropItem::ADropItem()
{
	static ConstructorHelpers::FClassFinder<UItemDropWnd> BP_ITEM_DROP_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/ItemDropWnd/BP_ItemDropWnd.BP_ItemDropWnd_C'"));
	if (BP_ITEM_DROP_WND.Succeeded()) ItemDropWndClass = BP_ITEM_DROP_WND.Class;
	else UE_LOG(LogTemp, Warning, TEXT("ADropItem.cpp::%d::LINE:: BP_ITEM_DROP_WND is not loaded! "), __LINE__);
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();


	Capsule->SetHiddenInGame(false);

	Capsule->SetCapsuleRadius(40.0f);
	Capsule->SetCapsuleHalfHeight(40.0f);

	Cast<UCharacterWidget>(CharacterWidget->GetUserWidgetObject())->SetNameText(FText::FromString(TEXT(" ")));
}

ADropItem* ADropItem::SpawnItem(UObject* contextObj, TArray<FItemSlotInfo> items, FVector location, FRotator rotation)
{
	ADropItem* newWorldItem = GEngine->GetWorldFromContextObject(contextObj)->
		SpawnActor<ADropItem>(ADropItem::StaticClass(), location, rotation);

	newWorldItem->Items = items;

	return newWorldItem;
}

void ADropItem::Interaction()
{
	auto itemRootWnd = GetManager(UPlayerManager)->GetPlayerController()->
		GetClosableWndControllerComponent()->AddWnd<UItemDropWnd>(ItemDropWndClass);

	itemRootWnd->InitializeRootItems(Items);
	itemRootWnd->SetDropItem(this);
	itemRootWnd->onWndClosed.AddLambda([this]() { FinishInteraction(); });
}
