#include "MercenaryAnimInstance.h"

#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Actors/Controllers/MercenaryController/MercenaryController.h"
#include "Components/MercenaryAttack/MercenaryAttackComponent.h"

void UMercenaryAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(Owner))
	{
		Owner = Cast<AMercenaryCharacter>(TryGetPawnOwner());
		return;
	}

	VelocityLength = Owner->GetVelocity().Size();

}

void UMercenaryAnimInstance::AnimNotify_KnightAttackFin()
{
	if (Owner->GetMercenaryAttack()->OnMercenaryAttackFinished.IsBound())
		Owner->GetMercenaryAttack()->OnMercenaryAttackFinished.Broadcast();
}

void UMercenaryAnimInstance::AnimNotify_KnightAttackRange()
{
	Owner->GetMercenaryAttack()->ActiveMercenaryAttackRange();
}

void UMercenaryAnimInstance::AnimNotify_UpdateRotation()
{
	Cast<AMercenaryController>(Owner->GetController())->IsLookatPlayer();
}

void UMercenaryAnimInstance::AnimNotify_Dash()
{
	Owner->MercenaryDash(Owner->GetActorForwardVector(), 1000.0f);
}
