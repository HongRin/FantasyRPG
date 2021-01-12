// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Actors/Controllers/MonsterController/MonsterController.h"
#include "Components/MonsterAttack/MonsterAttackComponent.h"

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	if (!IsValid(Owner))
	{
		Owner = Cast<AMonsterCharacter>(TryGetPawnOwner());
		return;
	}

	VelocityLength = Owner->GetVelocity().Size();
}

void UMonsterAnimInstance::AnimNotify_MonsterAttackFin()
{
	if (Owner->GetMonsterAttack()->OnMonsterAttackFinished.IsBound())
		Owner->GetMonsterAttack()->OnMonsterAttackFinished.Broadcast();

	Owner->GetMonsterInfo()->Atk = Owner->GetMonsterAtk();
}

void UMonsterAnimInstance::AnimNotify_UpdateRotation()
{
	Cast<AMonsterController>(Owner->GetController())->IsLookatPlayer();
}

void UMonsterAnimInstance::AnimNotify_AttackRange()
{
	Owner->GetMonsterAttack()->ActiveMonsterAttackRange();
}

void UMonsterAnimInstance::AnimNotify_MonsterDash()
{
	Owner->MonsterDash(Owner->GetActorForwardVector() , 3000.0f);
}
