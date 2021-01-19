#include "HealerState.h"
#include "Components/TextBlock.h"

void UHealerState::NativeConstruct()
{
	Super::NativeConstruct();

	Text_SkillCooldown = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillCooldown")));
	Text_BuffFigure = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_BuffFigure")));
	Text_HealingFigure = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HealingFigure")));
	Text_Hp = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Hp")));
	Text_SkillPercentage = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillPercentage")));
}

void UHealerState::UpdateHealerState(FMercenaryInfo* mercenaryInfo)
{
	Text_SkillCooldown->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), mercenaryInfo->SKillCoolDownTime)));
	Text_BuffFigure->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), mercenaryInfo->BuffAtkFigure)));
	Text_HealingFigure->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), mercenaryInfo->HealingFigure)));
	Text_Hp->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), mercenaryInfo->MaxHp)));
	Text_SkillPercentage->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), mercenaryInfo->SkillPercentage)));
}
