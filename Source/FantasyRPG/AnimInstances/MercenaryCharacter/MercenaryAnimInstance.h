#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MercenaryAnimInstance.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class AMercenaryCharacter* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float VelocityLength;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private :
	UFUNCTION()
	void AnimNotify_KnightAttackFin();

	UFUNCTION()
	void AnimNotify_KnightAttackRange();
};
