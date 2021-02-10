#include "PlayerManager.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"


void UPlayerManager::InitManagerClass()
{
}

ARPGPlayerController* UPlayerManager::GetPlayerController()
{
	if (!IsValid(PlayerController))
		PlayerController = Cast<ARPGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	return PlayerController;
}
