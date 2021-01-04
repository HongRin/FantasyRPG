#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MonsterCharacter/MonsterAnimInstance.h"
#include "BossMonsterAnimInstance.generated.h"

UCLASS()
class FANTASYRPG_API UBossMonsterAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
