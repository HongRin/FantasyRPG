#include "KnightState.h"
#include "Components/TextBlock.h"

void UKnightState::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Atk = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Atk")));
	Text_Hp = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Hp")));
	Text_SkillPercentage = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillPercentage")));
}

void UKnightState::UpdateKnightState(FMercenaryInfo* mercenaryInfo)
{
	Text_Atk->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), mercenaryInfo->Atk)));
	Text_Hp->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), mercenaryInfo->MaxHp)));
	Text_SkillPercentage->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), mercenaryInfo->SkillPercentage)));
}
