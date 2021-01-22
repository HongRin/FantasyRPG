#include "KnightReinforce.h"

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

UKnightReinforce::UKnightReinforce(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MR_RF_Info(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryReinforceInfo.DT_MercenaryReinforceInfo'"));
	if (DT_MR_RF_Info.Succeeded()) DT_MercenaryReinforceInfo = DT_MR_RF_Info.Object;
	else UE_LOG(LogTemp, Error, TEXT("UKnightReinforce.cpp::%d::LINE:: DT_MR_RF_Info is not loaded"), __LINE__);
}

void UKnightReinforce::NativeConstruct()
{
	Super::NativeConstruct();

	Text_HP = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HP")));
	Text_Atk = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Atk")));
	Text_SkillPercentage = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_SkillPercentage")));
	Text_ReinforceProbability = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ReinforceProbability")));
	Text_Cost = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Cost")));
	Button_Reinforce = Cast<UButton>(GetWidgetFromName(TEXT("Button_Reinforce")));

	Button_Reinforce->OnClicked.AddDynamic(this, &UKnightReinforce::KnightReinforceClicked);

	UpdateWndSize(700.0f, 400.0f);
}

void UKnightReinforce::UpdateKingitReinforce(FMercenaryInfo* mercenaryInfo)
{
	FString contextString;

	MercenaryReinforceInfo = DT_MercenaryReinforceInfo->FindRow<FMercenaryReinforceInfo>(
		mercenaryInfo->MercenaryReinforceCode, contextString);

	FText hpText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f"), mercenaryInfo->MaxHp) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f") , MercenaryReinforceInfo->MaxHp));
	Text_HP->SetText(hpText);

	FText atkText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f"), mercenaryInfo->Atk) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f"), MercenaryReinforceInfo->Atk));
	Text_Atk->SetText(atkText);

	FText skillPercentageText = (MercenaryReinforceInfo->bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString::Printf(TEXT("%.1f%%"), mercenaryInfo->SkillPercentage) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f%%"), MercenaryReinforceInfo->SkillPercentage));
	Text_SkillPercentage->SetText(skillPercentageText);

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

void UKnightReinforce::KnightReinforceClicked()
{
	if (MercenaryReinforceInfo->bMaximumLevel) return;

	UMercenaryStateComponent* mercenaryState = Cast<APlayerCharacter>(
		GetManager(UPlayerManager)->GetPlayerController()->GetPawn())->GetMercenaryState();

	for (int i = 0; i < mercenaryState->GetMercenaryActors().Num(); ++i)
	{
		if (mercenaryState->GetMercenaryActors()[i]->GetMercenaryInfo()->MercenaryType == EMercenaryType::MCT_KNIGHT)
		{
			FMercenaryInfo* mercenaryInfo = mercenaryState->GetMercenaryActors()[i]->GetMercenaryInfo();
			mercenaryInfo->MercenaryReinforceCode = MercenaryReinforceInfo->NextMercenaryReinforceCode;
			mercenaryInfo->MaxHp = MercenaryReinforceInfo->MaxHp;
			mercenaryInfo->Atk = MercenaryReinforceInfo->Atk;
			mercenaryInfo->SkillPercentage = MercenaryReinforceInfo->SkillPercentage;
			UpdateKingitReinforce(mercenaryInfo);
		}
	}
}
