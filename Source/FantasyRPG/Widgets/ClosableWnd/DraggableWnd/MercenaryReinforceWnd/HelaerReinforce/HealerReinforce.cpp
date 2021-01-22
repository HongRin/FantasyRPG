#include "HealerReinforce.h"
#include "Engine/DataTable.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"

#include "Enums/MercenaryType.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


UHealerReinforce::UHealerReinforce(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MR_RF_Info(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryReinforceInfo.DT_MercenaryReinforceInfo'"));
	if (DT_MR_RF_Info.Succeeded()) DT_MercenaryReinforceInfo = DT_MR_RF_Info.Object;
	else UE_LOG(LogTemp, Error, TEXT("UKnightReinforce.cpp::%d::LINE:: DT_MR_RF_Info is not loaded"), __LINE__);
}

void UHealerReinforce::NativeConstruct()
{
	Super::NativeConstruct();

	Text_HP = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HP")));
	Text_SkillCooldown = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillCooldown")));
	Text_SkillPercentage = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillPercentage")));
	Text_HealingFigure = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HealingFigure")));
	Text_BuffFigure = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_BuffFigure")));
	Text_ReinforceProbability = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ReinforceProbability")));
	Text_Cost = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Cost")));
	Button_Reinforce = Cast<UButton>(GetWidgetFromName(TEXT("Button_Reinforce")));

	Button_Reinforce->OnClicked.AddDynamic(this, &UHealerReinforce::HealerReinforceClicked);

	UpdateWndSize(700.0f, 560.0f);
}

void UHealerReinforce::UpdateHealerReinforce(FMercenaryInfo* mercenaryInfo)
{
	FString contextString;

	MercenaryReinforceInfo = DT_MercenaryReinforceInfo->FindRow<FMercenaryReinforceInfo>(
		mercenaryInfo->MercenaryReinforceCode, contextString);

	FText hpText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f"), mercenaryInfo->MaxHp) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f"), MercenaryReinforceInfo->MaxHp));
	Text_HP->SetText(hpText);

	FText sKillCoolDownTimeText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f 초"), mercenaryInfo->SKillCoolDownTime) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f 초"), MercenaryReinforceInfo->SKillCoolDownTime));
	Text_SkillCooldown->SetText(sKillCoolDownTimeText);

	FText skillPercentageText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f%%"), mercenaryInfo->SkillPercentage) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f%%"), MercenaryReinforceInfo->SkillPercentage));
	Text_SkillPercentage->SetText(skillPercentageText);

	FText healingFigureText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f"), mercenaryInfo->HealingFigure) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f"), MercenaryReinforceInfo->HealingFigure));
	Text_HealingFigure->SetText(healingFigureText);

	FText buffFigureText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f"), mercenaryInfo->BuffAtkFigure) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f"), MercenaryReinforceInfo->BuffAtkFigure));
	Text_BuffFigure->SetText(buffFigureText);

	FText reinforceProbabilityText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("")) :
		FText::FromString(FString::Printf(TEXT("%.1f%%"), MercenaryReinforceInfo->ReinforcementProbability));
	Text_ReinforceProbability->SetText(reinforceProbabilityText);

	FText costText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("")) :
		FText::FromString(
			FString::FromInt(MercenaryReinforceInfo->ReinforceCost));
	Text_Cost->SetText(costText);
}

void UHealerReinforce::HealerReinforceClicked()
{
	if (MercenaryReinforceInfo->bMaximumLevel) return;

	UMercenaryStateComponent* mercenaryState = Cast<APlayerCharacter>(
		GetManager(UPlayerManager)->GetPlayerController()->GetPawn())->GetMercenaryState();

	for (int i = 0; i < mercenaryState->GetMercenaryActors().Num(); ++i)
	{
		if (mercenaryState->GetMercenaryActors()[i]->GetMercenaryInfo()->MercenaryType == EMercenaryType::MCT_HEALER)
		{
			FMercenaryInfo* mercenaryInfo = mercenaryState->GetMercenaryActors()[i]->GetMercenaryInfo();
			mercenaryInfo->MercenaryReinforceCode = MercenaryReinforceInfo->NextMercenaryReinforceCode;
			mercenaryInfo->MaxHp = MercenaryReinforceInfo->MaxHp;
			mercenaryInfo->SKillCoolDownTime = MercenaryReinforceInfo->SKillCoolDownTime;
			mercenaryInfo->SkillPercentage = MercenaryReinforceInfo->SkillPercentage;
			mercenaryInfo->HealingFigure = MercenaryReinforceInfo->HealingFigure;
			mercenaryInfo->BuffAtkFigure = MercenaryReinforceInfo->BuffAtkFigure;

			UpdateHealerReinforce(mercenaryInfo);
		}
	}
}
