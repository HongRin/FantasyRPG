#include "PlayerAnimInstance.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/PlayerAttack/PlayerAttackComponent.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(Owner))
	{
		Owner = Cast<APlayerCharacter>(TryGetPawnOwner());
		return;
	}

	VelocityLength = Owner->GetVelocity().Size();
	bIsInAir = Owner->IsInAir();
	bIsDoubleJump = Owner->IsDoblueJump();
}

void UPlayerAnimInstance::AnimNotify_LFirstComboAttack()
{
	if (Owner->GetPlayerAttack()->LFirstComboAttackable())
		Montage_JumpToSection(TEXT("LAttack2"));
}

void UPlayerAnimInstance::AnimNotify_LSecondComboAttack()
{
	if (Owner->GetPlayerAttack()->LSecondComboAttackable())
		Montage_JumpToSection(TEXT("LAttack3"));
}

void UPlayerAnimInstance::AnimNotify_LComboAttackFin()
{
	if (Owner->GetPlayerAttack()->OnLComboAttackFinished.IsBound())
	{
		Owner->GetPlayerAttack()->OnLComboAttackFinished.Broadcast();
	}
}

void UPlayerAnimInstance::AnimNotify_RFirstComboAttack()
{
	if (Owner->GetPlayerAttack()->RFirstComboAttackable())
		Montage_JumpToSection(TEXT("RAttack2"));
}

void UPlayerAnimInstance::AnimNotify_RComboAttackFin()
{
	if (Owner->GetPlayerAttack()->OnRComboAttackFinished.IsBound())
	{
		Owner->GetPlayerAttack()->OnRComboAttackFinished.Broadcast();
	}
}

void UPlayerAnimInstance::AnimNotify_UpdateRotation()
{
	Owner->LookatControlDirection();
}

void UPlayerAnimInstance::AnimNotify_RegularAttackRange()
{
	Owner->GetPlayerAttack()->UpdateAttackRange(100.0f, 100.0f);
}

void UPlayerAnimInstance::AnimNotify_LAttackMove()
{
	Owner->PlayerAttackMove(Owner->GetActorForwardVector(), 1000.0f);
}

void UPlayerAnimInstance::AnimNotify_RAttackMove()
{
	Owner->PlayerAttackMove(Owner->GetActorForwardVector(), 5000.0f);
}

void UPlayerAnimInstance::AnimNotify_SkillMoveTest()
{
	Owner->PlayerAttackMove(Owner->GetActorForwardVector(), 12000.0f);
}

