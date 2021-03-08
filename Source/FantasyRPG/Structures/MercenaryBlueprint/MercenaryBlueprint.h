#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "MercenaryBlueprint.generated.h"

USTRUCT()
struct FANTASYRPG_API FMercenaryBlueprint : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MercenaryCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMercenaryCharacter> MercenaryBlueprint;
};
