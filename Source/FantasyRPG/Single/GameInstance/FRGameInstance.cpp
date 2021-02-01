#include "FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


void UFRGameInstance::Init()
{
	Super::Init();

	ManagerClasses.Empty();

	RegisterManagerClass(UPlayerManager::StaticClass());
}
void UFRGameInstance::Shutdown()
{

	for (int32 i = 0; i < ManagerClasses.Num(); ++i)
	{
		// nullptr 확인
		if (!ManagerClasses[i]) return;

		// 해당 객체가 GC 에 의해 해제된 객체인지 확인
		if (!ManagerClasses[i]->IsValidLowLevel()) return;
		/// - IsValidLowLevel() : GC 에 의해 해제되지 않았다면 true 리턴

		// 객체 소멸
		ManagerClasses[i]->ConditionalBeginDestroy();

		ManagerClasses[i] = nullptr;
	}

	Super::Shutdown();
}
void UFRGameInstance::RegisterManagerClass(TSubclassOf<UManagerClass> managerClass)
{
	UManagerClass* managerClassInstance = NewObject<UManagerClass>(this, managerClass,
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
	managerClassInstance->InitManagerClass();
	ManagerClasses.Add(managerClassInstance);
}