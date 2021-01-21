#pragma once

#include "FantasyRPG.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "HealerReinforce.generated.h"

UCLASS()
class FANTASYRPG_API UHealerReinforce : public UDraggableWnd
{
	GENERATED_BODY()
	
private:
	class UTextBlock* Text_HP;
	class UTextBlock* Text_SkillCooldown;
	class UTextBlock* Text_SkillPercentage;
	class UTextBlock* Text_HealingFigure;
	class UTextBlock* Text_BuffFigure;
	class UButton* Button_Reinforce;

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
