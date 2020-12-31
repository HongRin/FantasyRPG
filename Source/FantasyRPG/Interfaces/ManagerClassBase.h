#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ManagerClassBase.generated.h"

UINTERFACE(MinimalAPI)
class UManagerClassBase : public UInterface
{
	GENERATED_BODY()
};

class FANTASYRPG_API IManagerClassBase
{
	GENERATED_BODY()

public:
	virtual void InitManagerClass() PURE_VIRTUAL(IManagerClassBase::InitManagerClass, );
};
