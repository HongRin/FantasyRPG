#include "DungeonLevel.h"
#include "Engine/World.h"
#include "UserWidget.h"

ADungeonLevel::ADungeonLevel()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_RETURN_TO_TOWN(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/LoadingScreen/BP_ReturnToTown.BP_ReturnToTown_C'"));
	if (BP_RETURN_TO_TOWN.Succeeded()) BP_ReturnToTown = BP_RETURN_TO_TOWN.Class;
	else UE_LOG(LogTemp, Error, TEXT("ADungeonLevel.cpp::%d::LINE:: BP_RETURN_TO_TOWN is not loaded!"), __LINE__);
}

bool ADungeonLevel::DungeonClear()
{
	return (MonsterCharacters.Num() == 0);
}

void ADungeonLevel::ReturnToTown()
{
	CreateWidget<UUserWidget>(GetWorld(), BP_ReturnToTown)->AddToViewport();
}
