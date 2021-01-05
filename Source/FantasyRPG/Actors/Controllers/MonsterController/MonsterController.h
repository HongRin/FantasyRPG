#pragma once

#include "FantasyRPG.h"
#include "AIController.h"

#include "Perception/AIPerceptionTypes.h"

#include "MonsterController.generated.h"

UCLASS()
class FANTASYRPG_API AMonsterController : public AAIController
{
	GENERATED_BODY()

private :
	UPROPERTY()
	class AMonsterCharacter* MonsterCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	FName AIControllerCode;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* AISightConfig;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* MonsterBehaviorTree;
	
	UPROPERTY()
	class AActor* TrackingTargetActor;

	UPROPERTY()
	class UDataTable* AIControllerDatatable;

public :
	AMonsterController();

public :
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float dt) override;

public :
	void InitializeMonsterControllerConstructTime();

private :
	void InitializeMonsterController();

	bool IsPlayerNearby();

	void TrackingPlayer();

public :
	void IsLookatPlayer();

private :
	UFUNCTION()
	void OnSightDetected(AActor* Actor, FAIStimulus Stimulus);

public :
	FORCEINLINE AMonsterCharacter* GetMonsterCharacter() const
	{ return MonsterCharacter; }
};
