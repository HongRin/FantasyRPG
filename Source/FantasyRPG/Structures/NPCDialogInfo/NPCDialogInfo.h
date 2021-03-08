#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Widgets/ClosableWnd/ClosableDialogWnd/ClosableDialogWnd.h"
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
	TSubclassOf<UClosableDialogWnd> DialogClass;
	//FSoftObjectPath DialogClassPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText NPCDialog;
};
