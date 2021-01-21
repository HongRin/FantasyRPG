#include "KnightReinforce.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

UKnightReinforce::UKnightReinforce(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{

}

void UKnightReinforce::NativeConstruct()
{
	Super::NativeConstruct();

	Text_HP = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HP")));
	Text_Atk = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Atk")));
	Text_SkillPercentage = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillPercentage")));
	Button_Reinforce = Cast<UButton>(GetWidgetFromName(TEXT("Button_Reinforce")));

	Button_Reinforce->OnClicked.AddDynamic(this, &UKnightReinforce::KnightReinforceClicked);

	UpdateWndSize(700.0f, 320.0f);
}

void UKnightReinforce::UpdateKingitReinforce(FMercenaryInfo* mercenaryInfo)
{

}

void UKnightReinforce::KnightReinforceClicked()
{

}
