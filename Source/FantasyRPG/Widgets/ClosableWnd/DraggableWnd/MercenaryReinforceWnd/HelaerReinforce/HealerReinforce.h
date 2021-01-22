#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "Structures/MercenaryReinforceInfo/MercenaryReinforceInfo.h"
#include "HealerReinforce.generated.h"

UCLASS()
class FANTASYRPG_API UHealerReinforce : public UDraggableWnd
{
	GENERATED_BODY()
	
private:
	class UDataTable* DT_MercenaryReinforceInfo;

	class UTextBlock* Text_HP;
	class UTextBlock* Text_SkillCooldown;
	class UTextBlock* Text_SkillPercentage;
	class UTextBlock* Text_HealingFigure;
	class UTextBlock* Text_BuffFigure;
	class UTextBlock* Text_ReinforceProbability;
	class UTextBlock* Text_Cost;
	class UButton* Button_Reinforce;

	FMercenaryReinforceInfo* MercenaryReinforceInfo;


public:
	UHealerReinforce(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHealerReinforce(FMercenaryInfo* mercenaryInfo);

private:
	UFUNCTION()
	void HealerReinforceClicked();
};
