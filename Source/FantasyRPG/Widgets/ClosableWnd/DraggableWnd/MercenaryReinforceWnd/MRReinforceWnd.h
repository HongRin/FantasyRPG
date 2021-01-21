#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "MRReinforceWnd.generated.h"

UCLASS()
class FANTASYRPG_API UMRReinforceWnd : public UDraggableWnd
{
	GENERATED_BODY()

private :
	TSubclassOf<class UButtonList> BP_ButtonList;
	TSubclassOf<class UKnightReinforce>	BP_KnightReinforce;
	TSubclassOf<class UHealerReinforce> BP_HealerReinforce;

private:
	class UDataTable* DT_MercenaryInfo;
	class UScrollBox* ScrollBox_ButtonList;
	class UMercenaryStateComponent* MercenaryState;

public :
	UMRReinforceWnd(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	void InitializeButtonList();

public :
	void OpenReinforceWnd(FMercenaryInfo* mercenaryInfo);

};
