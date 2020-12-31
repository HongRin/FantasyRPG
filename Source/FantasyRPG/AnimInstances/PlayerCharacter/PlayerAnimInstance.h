#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class FANTASYRPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
	class APlayerCharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
	float VelocityLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner Properties")
	bool bIsDoubleJump;

public :
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private :
	UFUNCTION()
	void AnimNotify_LFirstComboAttack();

	UFUNCTION()
	void AnimNotify_LSecondComboAttack();
	
	UFUNCTION()
	void AnimNotify_LComboAttackFin();

	UFUNCTION()
	void AnimNotify_RFirstComboAttack();

	UFUNCTION()
	void AnimNotify_RComboAttackFin();

	UFUNCTION()
	void AnimNotify_UpdateRotation();

	UFUNCTION()
	void AnimNotify_RegularAttackRange();
	
	UFUNCTION()
	void AnimNotify_LAttackMove();

	UFUNCTION()
	void AnimNotify_RAttackMove();

	UFUNCTION()
	void AnimNotify_SkillMoveTest();

};
