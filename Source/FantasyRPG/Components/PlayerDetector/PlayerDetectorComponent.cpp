#include "PlayerDetectorComponent.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/FRGameInstance.h"

UPlayerDetectorComponent::UPlayerDetectorComponent()
{
	SphereRadius = 200.0f;
}

void UPlayerDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UPlayerDetectorComponent::OnPlayerDetected);
	OnComponentEndOverlap.AddDynamic(this, &UPlayerDetectorComponent::OnPlayerLost);
}

void UPlayerDetectorComponent::OnPlayerDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn()))
	{
		if (OtherComp == Cast<APlayerCharacter>(OtherActor)->GetCapsuleComponent())
			bDetectPlayer = true;
	}

	if (OtherActor->ActorHasTag(TEXT("Mercenary")))
	{
		if (OtherComp == Cast<AMercenaryCharacter>(OtherActor)->GetCapsuleComponent())
		{
			bDetectMercenary = true;
		}
	}

	if (OtherActor->ActorHasTag(TEXT("Monster")))
	{
		if (OtherComp == Cast<AMonsterCharacter>(OtherActor)->GetCapsuleComponent())
		{
			bDetectMonster = true;
		}
	}
}

void UPlayerDetectorComponent::OnPlayerLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn()))
	{
		if (OtherComp == Cast<APlayerCharacter>(OtherActor)->GetCapsuleComponent())
			bDetectPlayer = false;
	}

	if (OtherActor->ActorHasTag(TEXT("Mercenary")))
	{
		if (OtherComp == Cast<AMercenaryCharacter>(OtherActor)->GetCapsuleComponent())
		{
			bDetectMercenary = false;
		}
	}

	if (OtherActor->ActorHasTag(TEXT("Monster")))
	{
		if (OtherComp == Cast<AMonsterCharacter>(OtherActor)->GetCapsuleComponent())
		{
			bDetectMonster = false;
		}
	}
}
