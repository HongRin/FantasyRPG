#include "FRGameMode.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

AFRGameMode::AFRGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = ARPGPlayerController::StaticClass();
}