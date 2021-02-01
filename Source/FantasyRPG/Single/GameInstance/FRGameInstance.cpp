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
		// nullptr Ȯ��
		if (!ManagerClasses[i]) return;

		// �ش� ��ü�� GC �� ���� ������ ��ü���� Ȯ��
		if (!ManagerClasses[i]->IsValidLowLevel()) return;
		/// - IsValidLowLevel() : GC �� ���� �������� �ʾҴٸ� true ����

		// ��ü �Ҹ�
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