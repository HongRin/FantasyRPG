#pragma once

#include "CoreMinimal.h"
#include "FantasyRPG.h"
#include "UObject/NoExportTypes.h"
#include "ManagerClass.generated.h"

#ifndef MANAGER_INSTANCE
#define MANAGER_INSTANCE
#define GetManager(managerClassType) (Cast<UFRGameInstance>(GetWorld()->GetGameInstance())->GetManagerClass<managerClassType>())
#endif

UCLASS(Abstract)
class FANTASYRPG_API UManagerClass : public UObject
{

	GENERATED_BODY()

public:
	virtual void InitManagerClass() PURE_VIRTUAL(UManagerClass::InitManagerClass, );
};
