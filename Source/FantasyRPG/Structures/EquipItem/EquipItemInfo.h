#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/EquipItemType.h"
#include "EquipItemInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FEquipItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ItemCode;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EEquipItemType ItemType;

    // 추가 방어력
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalDefensiveForce;

    // 추가 공격력
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalOffensiveForce;

    // 아이템 장착 최소 레벨
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 MinLevel;

    // 추가 체력
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalHp;

    // 추가 마나
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalMp;

    // 강화 비용
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 ReinforcementCosts;

    // 강화 성공 확률
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ReinforcementProbability;

    // 해당 아이템의 레벨을 나타냅니다.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 ItemLevel;

    // 다음 강화 아이템 코드
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName NextReinforcementItemCode;

    // 최종 아이템임을 나타냅니다.
    /// - 해당 값이 참일 경우 더 이상 강화가 불가능한 아이템으로 인식됩니다.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bMaximumLevel;
};
