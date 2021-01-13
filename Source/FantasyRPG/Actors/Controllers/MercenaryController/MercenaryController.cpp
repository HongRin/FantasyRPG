#include "MercenaryController.h"

#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Components/PlayerDetector/PlayerDetectorComponent.h"
#include "Components/MercenaryAttack/MercenaryAttackComponent.h"


#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMercenaryController::AMercenaryController()
{

	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_MERCENARY(
		TEXT("BehaviorTree'/Game/Resources/AI/BT_Mercenary.BT_Mercenary'"));
	if (BT_MERCENARY.Succeeded()) MercenaryBehaviorTree = BT_MERCENARY.Object;

	InitializeMercenaryController();
}

void AMercenaryController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MercenaryCharacterInstance = Cast<AMercenaryCharacter>(InPawn);

	if (IsValid(MercenaryBehaviorTree))
	{
		RunBehaviorTree(MercenaryBehaviorTree);

		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,
			&AMercenaryController::OnSightDetected);
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("MonsterController.cpp :: %d LINE :: MercenaryBehaviorTree is not loaded !"), __LINE__);
	}


}

void AMercenaryController::BeginPlay()
{
	Super::BeginPlay();
}

void AMercenaryController::Tick(float dt)
{
	Super::Tick(dt);

	if (GetMercenaryCharacter()->IsMercenaryMovable())
	{
		if (IsValid(TrackingTargetActor))
		{
			if (!IsPlayerNearby())
			{
				TrackingActor();
			}
		}
		else
		{
			if (MercenaryCharacterInstance->GetMercenaryAttack()->OnMercenaryAttackFinished.IsBound())
				MercenaryCharacterInstance->GetMercenaryAttack()->OnMercenaryAttackFinished.Broadcast();
			MoveToActor(Cast<AActor>(MercenaryCharacterInstance->GetPlayerCharacter()));
		}
	}
}

void AMercenaryController::InitializeMercenaryController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION")));

	SetGenericTeamId(TEAM_MERCENRAY);
	
	{
		AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SIGHT_CONFIG"));

		AISightConfig->SightRadius = 400.0f;
		AISightConfig->LoseSightRadius = 500.0f;
		AISightConfig->PeripheralVisionAngleDegrees = 180.0f;
		AISightConfig->SetMaxAge(2.0f);

		AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
		AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;
		AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;

		GetPerceptionComponent()->ConfigureSense(*AISightConfig);
	}
}

bool AMercenaryController::IsPlayerNearby()
{
	bool nearby = false;

	
	if (IsValid(MercenaryCharacterInstance))
	{
		nearby = MercenaryCharacterInstance->GetPlayerDetector()->IsMonsterDetected();
	}
	
	GetBlackboardComponent()->SetValueAsBool(TEXT("MonsterIsNearby"), nearby);

	return nearby;
}

void AMercenaryController::TrackingActor()
{
	if (!IsValid(TrackingTargetActor)) return;
	
	if(TrackingTargetActor->ActorHasTag(TEXT("Monster")) || TrackingTargetActor->ActorHasTag(TEXT("BsMonster")))
	GetBlackboardComponent()->SetValueAsBool(TEXT("IsTracking"), true);
	
	MoveToActor(TrackingTargetActor);
}

void AMercenaryController::IsLookatPlayer()
{
	if (!IsValid(TrackingTargetActor)) return;

	FVector trackingLocation = TrackingTargetActor->GetActorLocation();
	FVector currentLocation = GetMercenaryCharacter()->GetActorLocation();

	FVector direction = trackingLocation - currentLocation;

	direction.Z = 0.0f;

	direction = direction.GetSafeNormal();

	MercenaryCharacterInstance->SetActorRotation(direction.Rotation());
}

void AMercenaryController::OnSightDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (IsValid(TrackingTargetActor)) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		if (Actor->ActorHasTag(TEXT("Monster")))
		{
			if (!IsValid(TrackingTargetActor))
				TrackingTargetActor = Actor;
		}
		if (Actor->ActorHasTag(TEXT("BsMonster")))
		{
			if (!IsValid(TrackingTargetActor))
				TrackingTargetActor = Actor;
		}
	}
	else
	{
		if (MercenaryCharacterInstance->GetMercenaryAttack()->OnMercenaryAttackFinished.IsBound())
			MercenaryCharacterInstance->GetMercenaryAttack()->OnMercenaryAttackFinished.Broadcast();
		TrackingTargetActor = nullptr;
	}
}
