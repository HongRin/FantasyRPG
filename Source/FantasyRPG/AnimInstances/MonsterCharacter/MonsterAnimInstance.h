
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UCLASS()
class FANTASYRPG_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class AMonsterCharacter* Owner;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float VelocityLength;
	
public :
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private :
	UFUNCTION()
	void AnimNotify_MonsterAttackFin();

	UFUNCTION()
	void AnimNotify_UpdateRotation();

	UFUNCTION()
	void AnimNotify_AttackRange();

	UFUNCTION()
	void AnimNotify_MonsterDash();

};
