#pragma once

#include "FantasyRPG.h"
#include "Components/ActorComponent.h"
#include "PlayerAttackComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(OnAttackEventSignatue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASYRPG_API UPlayerAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	OnAttackEventSignatue OnLComboAttackFinished;
	OnAttackEventSignatue OnRComboAttackFinished;

private :
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	class UAnimMontage* RegularAttackAnimMotage;

	bool bIsLRegularAttack;
	bool bIsLFirstComboAttack;
	bool bIsLSecondComboAttack;

	bool bIsRRegularAttack;
	bool bIsRFirstComboAttack;


public:	
	UPlayerAttackComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	void LoadAsset();

public :
	void LRegularAttack();
	void RRegularAttack();
	void UpdateAttackRange(float radius, float length);

	FORCEINLINE bool LRegularAttacking() const
	{ return bIsLRegularAttack; }
	FORCEINLINE bool LFirstComboAttackable() const
	{ return bIsLFirstComboAttack; }
	FORCEINLINE bool LSecondComboAttackable() const
	{ return bIsLSecondComboAttack; }

	FORCEINLINE bool RRegularAttacking() const
	{ return bIsRRegularAttack; }
	FORCEINLINE bool RFirstComboAttackable() const
	{ return bIsRFirstComboAttack; }
};
