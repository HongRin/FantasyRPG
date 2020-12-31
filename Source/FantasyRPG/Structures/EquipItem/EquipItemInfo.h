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

    // �߰� ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalDefensiveForce;

    // �߰� ���ݷ�
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalOffensiveForce;

    // ������ ���� �ּ� ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 MinLevel;

    // �߰� ü��
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalHp;

    // �߰� ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float AdditionalMp;

    // ��ȭ ���
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 ReinforcementCosts;

    // ��ȭ ���� Ȯ��
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ReinforcementProbability;

    // �ش� �������� ������ ��Ÿ���ϴ�.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 ItemLevel;

    // ���� ��ȭ ������ �ڵ�
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName NextReinforcementItemCode;

    // ���� ���������� ��Ÿ���ϴ�.
    /// - �ش� ���� ���� ��� �� �̻� ��ȭ�� �Ұ����� ���������� �νĵ˴ϴ�.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bMaximumLevel;
};
