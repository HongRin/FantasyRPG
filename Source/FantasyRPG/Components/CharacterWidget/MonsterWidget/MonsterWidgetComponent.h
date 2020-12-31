#pragma once

#include "FantasyRPG.h"
#include "Components/CharacterWidget/CharacterWidgetComponent.h"
#include "MonsterWidgetComponent.generated.h"

UCLASS()
class FANTASYRPG_API UMonsterWidgetComponent : public UCharacterWidgetComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TSubclassOf<class UHpableCharacterWidget> MonsterCharacterWidgetClass;

	UPROPERTY()
		class UHpableCharacterWidget* MonsterWidgetInstance;

	UPROPERTY()
		class AMonsterCharacter* MonsterCharacter;


public:
	UMonsterWidgetComponent();

protected:
	virtual void BeginPlay() override;

public:
	class UHpableCharacterWidget* GetEnemyWidgetInstance();


	
};
