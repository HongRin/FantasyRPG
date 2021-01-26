#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "DungeonChoiceWnd.generated.h"

UCLASS()
class FANTASYRPG_API UDungeonChoiceWnd : public UClosableWnd
{
	GENERATED_BODY()
	
private :
	class UButton* Button_Cancel;

protected :
	virtual void NativeConstruct() override;
};
