#pragma once

#include "FantasyRPG.h"
#include "Engine/LevelScriptActor.h"
#include "LoadingScreenLevel.generated.h"

UCLASS()
class FANTASYRPG_API ALoadingScreenLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UUserWidget> BP_LoadingScreen;

public:
	ALoadingScreenLevel();

protected:
	virtual void BeginPlay() override;


};
