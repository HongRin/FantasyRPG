#include "DungeonRow.h"

#include "Engine/DataTable.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Structures/DungeonRowInfo/DungeonRowInfo.h"

#include "Components/PlayerInventory/PlayerInventoryComponent.h"
#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

UDungeonRow::UDungeonRow(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DUNGEON_ROW_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_DungeonRowInfo.DT_DungeonRowInfo'"));
	if (DT_DUNGEON_ROW_INFO.Succeeded()) DT_DungeonRowInfo = DT_DUNGEON_ROW_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UDungeonRow.cpp::%d::LINE:: DT_DUNGEON_ROW_INFO is not loaded!"), __LINE__);
}

void UDungeonRow::NativeConstruct()
{
	Super::NativeConstruct();

	Button_EnterDungeon->OnClicked.AddDynamic(this, &UDungeonRow::ClickEnterDungeonButton);
}

void UDungeonRow::InitializeDungeonRow(FName dungeonCode)
{
	FString contextString;
	FDungeonRowInfo* dungeonRowInfo = DT_DungeonRowInfo->FindRow<FDungeonRowInfo>(dungeonCode, contextString);

	Text_Name->SetText(dungeonRowInfo->DungeonName);
	
	UFRGameInstance* gameInst = Cast<UFRGameInstance>(GetGameInstance());

	UTexture2D* dungeonImage =
		Cast<UTexture2D>(gameInst->GetStreamableManager()->LoadSynchronous(dungeonRowInfo->DungeonSpritePath));
	
	Image_DungeonSprite->SetBrushFromTexture(dungeonImage);

	NextDungeonName = dungeonRowInfo->NextMapName;
}

void UDungeonRow::ClickEnterDungeonButton()
{
	UPlayerManager* playerManger = GetManager(UPlayerManager);
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(playerManger->GetPlayerController()->GetPawn());
	UPlayerInventoryComponent* playerInventory = playerCharacter->GetPlayerInventory();
	UMercenaryStateComponent* mercenaryState = playerCharacter->GetMercenaryState();
	playerManger->SetPlayerInventoryItems(playerInventory->GetInventoryItems());
	playerManger->SetParticipateInfo(mercenaryState->GetParticipateInfo());

	Cast<UFRGameInstance>(GetGameInstance())->SetNextLevelName(NextDungeonName);
	UGameplayStatics::OpenLevel(this, FName(TEXT("LoadingLevel")));
}
