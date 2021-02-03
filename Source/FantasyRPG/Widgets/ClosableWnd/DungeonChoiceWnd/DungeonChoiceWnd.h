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
	TSubclassOf<class UParticipateRow> BP_ParticipateRow;

private :
	class UDataTable* DT_DCWInfo;

	class UScrollBox* ScrollBox_DungeonList;
	class UScrollBox* ScrollBox_Participate;

	class UButton* Button_Cancel;

	class UMercenaryStateComponent* MercenaryState;

public :
	UDungeonChoiceWnd(const FObjectInitializer& ObjectInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	void UpdateParticipate();

private :
	UFUNCTION()
	void QuitDundeonWnd();

public :
	void InitializeDCW(FName dcwCode);

	FORCEINLINE class UMercenaryStateComponent* GetMercenaryState() const
	{ return MercenaryState; }
};
