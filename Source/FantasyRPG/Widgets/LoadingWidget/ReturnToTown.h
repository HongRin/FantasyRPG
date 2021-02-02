#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReturnToTown.generated.h"

UCLASS()
class FANTASYRPG_API UReturnToTown : public UUserWidget
{
	GENERATED_BODY()

private :
	class UTextBlock* Text_Loading;
	
	int32 Time;

protected :
	virtual void NativeConstruct() override;
};
