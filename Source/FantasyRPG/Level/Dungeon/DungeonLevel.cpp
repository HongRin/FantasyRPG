#include "DungeonLevel.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "UserWidget.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Components/PlayerInventory/PlayerInventoryComponent.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Structures/MercenaryBlueprint/MercenaryBlueprint.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"


ADungeonLevel::ADungeonLevel()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_RETURN_TO_TOWN(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/LoadingScreen/BP_ReturnToTown.BP_ReturnToTown_C'"));
	if (BP_RETURN_TO_TOWN.Succeeded()) BP_ReturnToTown = BP_RETURN_TO_TOWN.Class;
	else UE_LOG(LogTemp, Error, TEXT("ADungeonLevel.cpp::%d::LINE:: BP_RETURN_TO_TOWN is not loaded!"), __LINE__);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_BP(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryBlueprint.DT_MercenaryBlueprint'"));
	if (DT_MERCENARY_BP.Succeeded()) DT_MercenaryBP = DT_MERCENARY_BP.Object;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryStateComponent.cpp::%d::LINE:: DT_MERCENARY_BP is not loaded!"), __LINE__);
}

void ADungeonLevel::BeginPlay()
{
	Super::BeginPlay();

}

bool ADungeonLevel::DungeonClear()
{
	return (MonsterCharacters.Num() == 0);
}

void ADungeonLevel::ReturnToTown()
{
	UPlayerManager* playerManger = GetManager(UPlayerManager);
	UPlayerInventoryComponent* playerInventory = Cast<APlayerCharacter>(playerManger->GetPlayerController()->GetPawn())->GetPlayerInventory();
	playerManger->SetPlayerInventoryItems(playerInventory->GetInventoryItems());

	CreateWidget<UUserWidget>(GetWorld(), BP_ReturnToTown)->AddToViewport();
}

void ADungeonLevel::SpawnMercenary()
{
}
