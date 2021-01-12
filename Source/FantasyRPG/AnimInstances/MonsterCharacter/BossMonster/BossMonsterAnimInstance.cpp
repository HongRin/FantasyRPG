#include "BossMonsterAnimInstance.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Actors/Controllers/MonsterController/MonsterController.h"
#include "Components/MonsterAttack/MonsterAttackComponent.h"

void UBossMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UBossMonsterAnimInstance::AnimNotify_SkillJump()
{
	Owner->MonsterDash(Owner->GetActorForwardVector() + FVector::UpVector, 500.0f);

	Owner->GetMonsterInfo()->Atk *= 3;
}
