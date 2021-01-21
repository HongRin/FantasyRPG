#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "KnightReinforce.generated.h"

UCLASS()
class FANTASYRPG_API UKnightReinforce : public UDraggableWnd
{
	GENERATED_BODY()

private :
	class UTextBlock* Text_HP;
	class UTextBlock* Text_Atk;
	class UTextBlock* Text_SkillPercentage;
	class UButton* Button_Reinforce;

public :
	UKnightReinforce(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void UpdateKingitReinforce(FMercenaryInfo* mercenaryInfo);

private :
	UFUNCTION()
	void KnightReinforceClicked();


};
