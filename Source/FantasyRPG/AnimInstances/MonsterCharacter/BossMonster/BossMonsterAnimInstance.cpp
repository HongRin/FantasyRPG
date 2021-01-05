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
	FVector direction = FVector::UpVector;
	direction += Owner->GetActorForwardVector();
	Owner->MonsterDash(direction , 1000.0f);
}
