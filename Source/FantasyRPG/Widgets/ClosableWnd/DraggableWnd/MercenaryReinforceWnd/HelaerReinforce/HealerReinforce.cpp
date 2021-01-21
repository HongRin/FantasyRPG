#include "HealerReinforce.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UHealerReinforce::UHealerReinforce(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{
}

void UHealerReinforce::NativeConstruct()
{
	Super::NativeConstruct();

	Text_HP = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HP")));
	Text_SkillCooldown = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillCooldown")));
	Text_SkillPercentage = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillPercentage")));
	Text_HealingFigure = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HealingFigure")));
	Text_BuffFigure = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_BuffFigure")));
	Button_Reinforce = Cast<UButton>(GetWidgetFromName(TEXT("Button_Reinforce")));

	Button_Reinforce->OnClicked.AddDynamic(this, &UHealerReinforce::HealerReinforceClicked);

	UpdateWndSize(700.0f, 480.0f);
}

void UHealerReinforce::UpdateHealerReinforce(FMercenaryInfo* mercenaryInfo)
{

}

void UHealerReinforce::HealerReinforceClicked()
{

}
