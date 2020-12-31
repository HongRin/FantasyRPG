#include "Task_MercenaryAttack.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Actors/Controllers/MercenaryController/MercenaryController.h"
#include "Components/MercenaryAttack/MercenaryAttackComponent.h"


EBTNodeResult::Type UTask_MercenaryAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMercenaryController* mercenaryController = Cast<AMercenaryController>(OwnerComp.GetAIOwner());
	AMercenaryCharacter* mercenaryCharacter = mercenaryController->GetMercenaryCharacter();

	mercenaryCharacter->GetMercenaryAttack()->PlayMercenaryAttackAnimation();

	return EBTNodeResult::Type::Succeeded;
}