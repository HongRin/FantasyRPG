#pragma once

#include "FantasyRPG.h"
#include "Engine/LevelScriptActor.h"
#include "DungeonLevel.generated.h"

UCLASS()
class FANTASYRPG_API ADungeonLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private :
	TSubclassOf<class UUserWidget> BP_ReturnToTown;

private :
	TArray<class AMonsterCharacter*> MonsterCharacters;

	bool ExistBossMonster;

public :
	ADungeonLevel();

public :
	bool DungeonClear();
	
	void ReturnToTown();

public :
	FORCEINLINE void AddMonsterCharacters(class AMonsterCharacter* monsterCharacter)
	{ MonsterCharacters.Add(monsterCharacter); }

	FORCEINLINE void RemoveMonsterCharacters(class AMonsterCharacter* monsterCharacter)
	{ MonsterCharacters.Remove(monsterCharacter); }
};
