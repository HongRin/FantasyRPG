
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Perception/AIPerceptionTypes.h"

#include "MercenaryController.generated.h"

UCLASS()
class FANTASYRPG_API AMercenaryController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class AMercenaryCharacter* MercenaryCharacterInstance;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UAISenseConfig_Sight* AISightConfig;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* MercenaryBehaviorTree;

	UPROPERTY()
	class AActor* TrackingTargetActor;

public :
	AMercenaryController();

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;

private:
	void InitializeMercenaryController();

	bool IsPlayerNearby();

	void TrackingActor();

public:
	void IsLookatPlayer();

private:
	UFUNCTION()
		void OnSightDetected(AActor* Actor, FAIStimulus Stimulus);

public:
	FORCEINLINE class AMercenaryCharacter* GetMercenaryCharacter() const
	{
		return MercenaryCharacterInstance;
	}
};
