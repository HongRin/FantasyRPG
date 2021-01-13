#pragma once

#include "FantasyRPG.h"
#include "AIController.h"
#include "HealerController.generated.h"

UCLASS()
class FANTASYRPG_API AHealerController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
		class AMercenaryCharacter* HealerCharacterInstance;

	float LastDashTime;

public :
	AHealerController();

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float dt) override;

private :
	bool IsPlayerNearby();

	void PlaySkill();
};
