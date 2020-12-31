#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FPlayerInfo
{
    GENERATED_USTRUCT_BODY()

public:
    // �÷��̾� ĳ���� �ȱ� �ӷ�
    float WalkSpeed;

    // �÷��̾� ĳ���� �޸��� �ӷ�
    float RunSpeed;

    UPROPERTY()
    float MaxHp;

    UPROPERTY()
    float Hp;

    UPROPERTY()
    float Mp;

    UPROPERTY()
    float MaxMp;

    UPROPERTY()
    float Atk;

    UPROPERTY()
    float Def;

    UPROPERTY()
    int32 StatPoint;

    UPROPERTY()
    int32 InventorySlotConut;

    UPROPERTY()
    int32 Money;

public:
    FPlayerInfo();

    void Initialize();
};
