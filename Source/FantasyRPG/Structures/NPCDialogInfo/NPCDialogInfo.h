#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NPCDialogInfo.generated.h"


USTRUCT()
struct FANTASYRPG_API FNPCDialogInfo : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NPCCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MonsterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath DialogClassPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText NPCDialog;
};
