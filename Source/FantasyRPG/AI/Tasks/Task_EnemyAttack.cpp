#include "Task_EnemyAttack.h"

#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Actors/Controllers/MonsterController/MonsterController.h"
#include "Components/MonsterAttack/MonsterAttackComponent.h"

EBTNodeResult::Type UTask_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMonsterController* monsterController = Cast<AMonsterController>(OwnerComp.GetAIOwner());
	AMonsterCharacter* monsterCharacter = monsterController->GetMonsterCharacter();

	monsterCharacter->GetMonsterAttack()->PlayMonsterAttackAnimation();

	return EBTNodeResult::Type::Succeeded;
}