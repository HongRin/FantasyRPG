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
	// 객체를 구분할 일이 있을 경우 사용됩니다.
	virtual int32 GetID() const PURE_VIRTUAL(IObjectPoolable::GetID, return 0;);

	// 재사용 가능 여부를 나타내는 변수에 대한 접근자 / 설정자
	virtual bool GetCanRecyclable() const PURE_VIRTUAL(IObjectPoolable::GetCanRecyclable, return true;);
	virtual void SetCanRecyclable(bool canRecyclable) PURE_VIRTUAL(IObjectPoolable::SetCanRecyclable, );

	// 재활용이 되는 시점에서 호출되는 메서드
	virtual void OnRecycleStart() PURE_VIRTUAL(IObjectPoolable::OnRecycleStart, );
};
