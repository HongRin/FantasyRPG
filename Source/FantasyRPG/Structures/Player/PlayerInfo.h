#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FPlayerInfo
{
    GENERATED_USTRUCT_BODY()

public:
    // 플레이어 캐릭터 걷기 속력
    float WalkSpeed;

    // 플레이어 캐릭터 달리기 속력
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
