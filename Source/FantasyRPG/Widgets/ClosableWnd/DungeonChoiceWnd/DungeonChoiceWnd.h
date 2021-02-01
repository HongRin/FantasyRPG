#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "DungeonChoiceWnd.generated.h"


UCLASS()
class FANTASYRPG_API UDungeonChoiceWnd : public UClosableWnd
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UDungeonRow> BP_DungeonRow;

private :
	class UDataTable* DT_DCWInfo;

	class UScrollBox* ScrollBox_DungeonList;

	class UButton* Button_Cancel;

public :
	UDungeonChoiceWnd(const FObjectInitializer& ObjectInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	UFUNCTION()
	void QuitDundeonWnd();

public :
	void InitializeDCW(FName dcwCode);
};
