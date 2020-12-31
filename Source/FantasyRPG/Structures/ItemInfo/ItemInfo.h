#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/ItemType.h"
#include "Enums/ItemRatingType.h"
#include "ItemInfo.generated.h"

USTRUCT()
struct FANTASYRPG_API FItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ������ �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemCode;

	//������ Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType;

	// ������ ���Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemRatingType ItemRatingType;

	// ������ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemDescriptin;

	// �ִ� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxCount;

	// ������ �Ǹ� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SalePrice;

	// ������ ��������Ʈ �̹��� ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath ItemSpritePath;

	// ��Ÿ ��ġ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float value3;
};
