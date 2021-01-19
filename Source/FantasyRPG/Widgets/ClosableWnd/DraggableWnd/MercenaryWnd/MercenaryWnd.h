#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "MercenaryWnd.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryWnd : public UDraggableWnd
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UHealerState> BP_HealerState;
	TSubclassOf<class UKnightState> BP_KnightState;

	class UDataTable* DT_MercenaryInfo;

	class UMercenaryStateComponent* MercenaryState;

	class UScrollBox* ScrollBox_MercenaryList;

public:
	UMercenaryWnd(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;

public :
	void InitializeMercenaryWnd();

};
