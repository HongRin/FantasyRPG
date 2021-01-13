#include "HealerController.h"

#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Components/PlayerDetector/PlayerDetectorComponent.h"
#include "Components/HealerBehavior/HealerBehaviorComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AHealerController::AHealerController()
{
	PrimaryActorTick.bCanEverTick = true;

	SetGenericTeamId(TEAM_MERCENRAY);
}

void AHealerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	HealerCharacterInstance = Cast<AMercenaryCharacter>(InPawn);
}

void AHealerController::BeginPlay()
{
	Super::BeginPlay();
}

void AHealerController::Tick(float dt)
{
	Super::Tick(dt);

	PlaySkill();

	if (HealerCharacterInstance->IsHealerMovable() && !IsPlayerNearby())
	{
		MoveToActor(Cast<AActor>(HealerCharacterInstance->GetPlayerCharacter()));
	}
}

bool AHealerController::IsPlayerNearby()
{
	return HealerCharacterInstance->GetPlayerDetector()->IsPlayerDetected();
}

void AHealerController::PlaySkill()
{
	if (!IsPlayerNearby()) return;

	if (HealerCharacterInstance->GetMercenaryInfo()->SKillCoolDownTime >= GetWorld()->GetTimeSeconds() - LastDashTime) return;

	LastDashTime = GetWorld()->GetTimeSeconds();
	HealerCharacterInstance->GetHealerBehavior()->PlayHealingAnimation();
}

