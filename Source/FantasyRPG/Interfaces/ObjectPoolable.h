#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolable.generated.h"

UINTERFACE(MinimalAPI)
class UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};

class FANTASYRPG_API IObjectPoolable
{
	GENERATED_BODY()

public:
	// ��ü�� ������ ���� ���� ��� ���˴ϴ�.
	virtual int32 GetID() const PURE_VIRTUAL(IObjectPoolable::GetID, return 0;);

	// ���� ���� ���θ� ��Ÿ���� ������ ���� ������ / ������
	virtual bool GetCanRecyclable() const PURE_VIRTUAL(IObjectPoolable::GetCanRecyclable, return true;);
	virtual void SetCanRecyclable(bool canRecyclable) PURE_VIRTUAL(IObjectPoolable::SetCanRecyclable, );

	// ��Ȱ���� �Ǵ� �������� ȣ��Ǵ� �޼���
	virtual void OnRecycleStart() PURE_VIRTUAL(IObjectPoolable::OnRecycleStart, );
};
