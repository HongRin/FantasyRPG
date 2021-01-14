#include "PlayerWndControllerComponent.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"
#include "Components/PlayerInventory/PlayerInventoryComponent.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Structures/Player/PlayerInfo.h"

#include "Widgets/ClosableWnd/DraggableWnd/StatusWnd/StatusWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/StatusWnd/StatusWndRow.h"
#include "Widgets/ClosableWnd/DraggableWnd/InventoryWnd/InventoryWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/MercenaryWnd/MercenaryWnd.h"

UPlayerWndControllerComponent::UPlayerWndControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


	static ConstructorHelpers::FClassFinder<UStatusWnd> BP_STATUS(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/StatusWnd/BP_StatusWnd.BP_StatusWnd_C'"));
	if (BP_STATUS.Succeeded()) BPStatusWndClass = BP_STATUS.Class;
	else UE_LOG(LogTemp, Error, TEXT("PlayerWndControllerComponent.cpp :: %d LINE :: BP_STATUS is not loaded!"), __LINE__);

	static ConstructorHelpers::FClassFinder<UInventoryWnd> BP_INVENTORY(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/InventoryWnd/BP_InventoryWnd.BP_InventoryWnd_C'"));
	if (BP_INVENTORY.Succeeded()) BPInventoryWndClass = BP_INVENTORY.Class;
	else UE_LOG(LogTemp, Error, TEXT("PlayerWndControllerComponent.cpp :: %d LINE :: BP_INVENTORY is not loaded!"), __LINE__);

	static ConstructorHelpers::FClassFinder<UMercenaryWnd> BP_MERCENARY_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryWnd/BP_MercenaryWnd.BP_MercenaryWnd_C'"));
	if (BP_MERCENARY_WND.Succeeded()) BPMercenaryWndClass = BP_MERCENARY_WND.Class;
	else UE_LOG(LogTemp, Error, TEXT("PlayerWndControllerComponent.cpp :: %d LINE :: BP_INVENTORY is not loaded!"), __LINE__);
}


void UPlayerWndControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	ClosableWndController = (GetManager(UPlayerManager)->GetPlayerController())->GetClosableWndControllerComponent();

	PlayerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>((GetManager(UPlayerManager)->GetPlayerController())->GetPawn());

	PlayerInventory = playerCharacter->GetPlayerInventory();
}

void UPlayerWndControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerWndControllerComponent::OpenStatus()
{
	// 스테이터스 창 객체를 생성합니다.
	StatusWnd = ClosableWndController->AddWnd<UStatusWnd>(BPStatusWndClass);

	StatusWnd->UpdateStatPointText(FText::FromString(FString::FromInt(PlayerInfo->StatPoint)));
}

void UPlayerWndControllerComponent::CloseStatus()
{
	ClosableWndController->CloseWnd(false, StatusWnd);

	StatusWnd = nullptr;
}

void UPlayerWndControllerComponent::OpenInventory()
{
	// 인벤토리 창 위젯을 생성합니다.
	InventoryWnd = ClosableWndController->AddWnd<UInventoryWnd>(BPInventoryWndClass);

	// 인벤토리 컴포넌트를 설정합니다.
	 InventoryWnd->InitializeInventoryWnd(PlayerInventory);
}

void UPlayerWndControllerComponent::CloseInventory()
{
	ClosableWndController->CloseWnd(false, InventoryWnd);

	InventoryWnd = nullptr;
}

void UPlayerWndControllerComponent::OpenMercenaryWnd()
{
	MercenaryWnd = ClosableWndController->AddWnd<UMercenaryWnd>(BPMercenaryWndClass);
}

void UPlayerWndControllerComponent::CloseMercenaryWnd()
{
	ClosableWndController->CloseWnd(false, MercenaryWnd);
	
	MercenaryWnd = nullptr;
}
