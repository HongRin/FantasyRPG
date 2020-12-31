#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterAttackComponent.generated.h"

#ifndef MONSTER_ATTACK_TYPE
#define MONSTER_ATTACK_TYPE
			   
#define MONSTER_ATTACK_NONE -1
#define MONSTER_ATTACK_BASIC 0
#define MONSTER_ATTACK_SKILL 1

#endif 

DECLARE_MULTICAST_DELEGATE(FOnMonsterAttackEventSignature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASYRPG_API UMonsterAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public :
	FOnMonsterAttackEventSignature OnMonsterAttackStarted;
									 
	FOnMonsterAttackEventSignature OnMonsterAttackFinished;

private :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (UIMin = "0.0", UIMax = "90.0", ClampMin = "0.0", ClampMax = "90.0", AllowPrivateAccess = "true"))
	float SkillPercentage;

	UPROPERTY()
	class AMonsterCharacter* MonsterCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* MonsterAttack;

	UPROPERTY()
	int32 AttackState;

public:	
	UMonsterAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	void PlayMonsterAttackAnimation();

	void ActiveMonsterAttackRange();

	FORCEINLINE bool IsMonsterAttacking() const
	{ return AttackState != MONSTER_ATTACK_NONE; };
};
