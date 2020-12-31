
#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ObjectPoolable.h"
#include "ObjectPool.generated.h"

UCLASS()
class FANTASYRPG_API UObjectPool : public UObject
{
	GENERATED_BODY()
	
private:
	// Ǯ���� ������Ʈ���� ������ �迭
	TArray<IObjectPoolable*> PoolObjects;

public:
	// Ǯ���� ���ο� ������Ʈ�� ����մϴ�.
	template<typename T>
	T* RegisterRecyclableObject(T* newRecyclableObject)
	{
		PoolObjects.Add((IObjectPoolable*)newRecyclableObject);
		return newRecyclableObject;
	}

	// ��Ȱ��� ��ü�� ����ϴ�.
	/// - callOnRecycleStart : ���� ������ ��ü�� ã���� ��� OnRecycleStart() �� ȣ���ų �������� �����մϴ�.
	IObjectPoolable* GetRecycledObject();
};
