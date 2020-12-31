#include "FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


void UFRGameInstance::Init()
{
	Super::Init();

	ManagerClasses.Empty();

	RegisterManagerClass(UPlayerManager::StaticClass());
}
void UFRGameInstance::RegisterManagerClass(TSubclassOf<UManagerClass> managerClass)
{
	UManagerClass* managerClassInstance = NewObject<UManagerClass>(this, managerClass);
	managerClassInstance->InitManagerClass();
	ManagerClasses.Add(managerClassInstance);
}