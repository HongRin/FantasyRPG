#include "FRGameMode.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

AFRGameMode::AFRGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerCharacter>RPG_PLAYER_CHARACTER(TEXT("Blueprint'/Game/Resources/Blueprints/Character/PlayerCharacter/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (RPG_PLAYER_CHARACTER.Succeeded()) DefaultPawnClass = RPG_PLAYER_CHARACTER.Class;

	PlayerControllerClass = ARPGPlayerController::StaticClass();
}