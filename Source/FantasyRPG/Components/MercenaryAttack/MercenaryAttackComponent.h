#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MercenaryAttackComponent.generated.h"


#ifndef MERCENARY_ATTACK_TYPE
#define MERCENARY_ATTACK_TYPE

#define MERCENARY_ATTACK_NONE -1
#define MERCENARY_ATTACK_BASIC 0
#define MERCENARY_ATTACK_SKILL 1
#endif

DECLARE_MULTICAST_DELEGATE(FOnMercenaryAttackEventSignature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASYRPG_API UMercenaryAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnMercenaryAttackEventSignature OnMercenaryAttackStarted;

	FOnMercenaryAttackEventSignature OnMercenaryAttackFinished;

private:
	UPROPERTY()
	class AMercenaryCharacter* MercenaryCharacter;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* MercenaryAttack;

	UPROPERTY()
	int32 AttackState;

public:	
	UMercenaryAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void PlayMercenaryAttackAnimation();

	void ActiveMercenaryAttackRange();

	FORCEINLINE bool IsMercenaryAttacking() const
	{
		return AttackState != MERCENARY_ATTACK_NONE;
	};
};
