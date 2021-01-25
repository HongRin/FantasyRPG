#pragma once

#include "FantasyRpg.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "MercenaryHpWnd.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMercenaryTakeDamageEventSignatue)

UCLASS()
class FANTASYRPG_API UMercenaryHpWnd : public UClosableWnd
{
	GENERATED_BODY()

public :
	FOnMercenaryTakeDamageEventSignatue OnTakeDamageEvent;
	
private :
	TSubclassOf<class UMercenaryHpRow> BP_MercenaryHpRow;

private :
	class UVerticalBox* VerticalBox_List;
	class UMercenaryStateComponent* MercenaryState;


public :
	UMercenaryHpWnd();

protected :
	virtual void NativeConstruct() override;

public :
	void AddMercenaryHpList(FMercenaryInfo* mercenaryInfo);
};
