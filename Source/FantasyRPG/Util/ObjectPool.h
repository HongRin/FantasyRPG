
#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ObjectPoolable.h"
#include "ObjectPool.generated.h"

UCLASS()
class FANTASYRPG_API UObjectPool : public UObject
{
	GENERATED_BODY()
	
private:
	// 풀링할 오브젝트들을 저장할 배열
	TArray<IObjectPoolable*> PoolObjects;

public:
	// 풀링할 새로운 오브젝트를 등록합니다.
	template<typename T>
	T* RegisterRecyclableObject(T* newRecyclableObject)
	{
		PoolObjects.Add((IObjectPoolable*)newRecyclableObject);
		return newRecyclableObject;
	}

	// 재활용된 객체를 얻습니다.
	/// - callOnRecycleStart : 재사용 가능한 객체를 찾았을 경우 OnRecycleStart() 를 호출시킬 것인지를 결정합니다.
	IObjectPoolable* GetRecycledObject();
};
