#include "MonsterController.h"

#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Components/PlayerDetector/PlayerDetectorComponent.h"
#include "Components/MonsterAttack/MonsterAttackComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMonsterController::AMonsterController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_MONSTER(
		TEXT("BehaviorTree'/Game/Resources/AI/BT_Monster.BT_Monster'"));
	if (BT_MONSTER.Succeeded()) MonsterBehaviorTree = BT_MONSTER.Object;

	InitializeMonsterController();
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MonsterCharacter = Cast<AMonsterCharacter>(InPawn);

	if (IsValid(MonsterBehaviorTree))
	{
		RunBehaviorTree(MonsterBehaviorTree);

		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,
			&AMonsterController::OnSightDetected);
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("MonsterController.cpp :: %d LINE :: MonseterBehaviorTree is not loaded !"), __LINE__);
	}

	MonsterCharacter->GetMonsterAttack()->OnMonsterAttackStarted.AddUObject(
		this, &AMonsterController::IsLookatPlayer);

	MonsterCharacter->GetMonsterAttack()->OnMonsterAttackStarted.AddLambda([this]()->void
	{ MoveToActor(MonsterCharacter); });
}

void AMonsterController::Tick(float dt)
{
	Super::Tick(dt);


	if (GetMonsterCharacter()->IsMovable())
	{
		if (!IsPlayerNearby())
			TrackingPlayer();
	}
}



void AMonsterController::InitializeMonsterController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION")));

	SetGenericTeamId(TEAM_MONSTER);

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

bool AMonsterController::IsPlayerNearby()
{
	bool nearby = false;

	if (IsValid(MonsterCharacter))
	{
		nearby = MonsterCharacter->GetPlayerDetector()->IsPlayerDetected();
	}

	GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerIsNearby"), nearby);

	return nearby;
}

void AMonsterController::TrackingPlayer()
{
	if (!IsValid(TrackingTargetActor)) return;

	GetBlackboardComponent()->SetValueAsBool(TEXT("IsTracking"), true);

	MoveToActor(TrackingTargetActor);
}

void AMonsterController::IsLookatPlayer()
{
	if (!IsValid(TrackingTargetActor)) return;

	FVector trackingLocation = TrackingTargetActor->GetActorLocation();
	FVector currentLocation = GetMonsterCharacter()->GetActorLocation();

	FVector direction = trackingLocation - currentLocation;

	direction.Z = 0.0f;

	direction = direction.GetSafeNormal();

	MonsterCharacter->SetActorRotation(direction.Rotation());
}

void AMonsterController::OnSightDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (!IsValid(TrackingTargetActor))
			TrackingTargetActor = Actor;
	}
	else
		TrackingTargetActor = nullptr;
}
