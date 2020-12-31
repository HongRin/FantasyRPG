#pragma once

#include "FantasyRPG.h"
#include "Engine/GameInstance.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

//#include "Interfaces/ManagerClassBase.h"
#include "Single/ManagerClass/ManagerClass.h"

#include "FRGameInstance.generated.h"

UCLASS()
class FANTASYRPG_API UFRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	TArray<UManagerClass*> ManagerClasses;


private:
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public:
	virtual void Init() override;

	template<typename ManagerClassType>
	ManagerClassType* GetManagerClass()
	{
		for (int i = 0; i < ManagerClasses.Num(); ++i)
		{
			if (ManagerClasses[i]->GetClass() == ManagerClassType::StaticClass())
				return  Cast<ManagerClassType>(ManagerClasses[i]);
		}

		return nullptr;
	}

public :
	FORCEINLINE FStreamableManager* GetStreamableManager()
	{ return &UAssetManager::GetStreamableManager(); }

};
