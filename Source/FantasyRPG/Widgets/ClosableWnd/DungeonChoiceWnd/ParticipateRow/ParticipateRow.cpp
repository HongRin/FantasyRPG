#include "ParticipateRow.h"

#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"

#include "Widgets/ClosableWnd/DungeonChoiceWnd/DungeonChoiceWnd.h"

#include "Structures/MercenaryInfo/MercenaryInfo.h"

#include "Engine/DataTable.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UParticipateRow::UParticipateRow(const FObjectInitializer& objInitializer) :
	Super(objInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCERNARY_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryInfo.DT_MercenaryInfo'"));
	if (DT_MERCERNARY_INFO.Succeeded()) DT_MercenaryInfo = DT_MERCERNARY_INFO.Object;
	else UE_LOG(LogTemp, Warning, TEXT("UParticipateRow.cpp::%d::LINE:: DT_MERCERNARY_INFO is not loaded!"), __LINE__)
}

void UParticipateRow::NativeConstruct()
{
	Super::NativeConstruct();

	CheckBox_Participate->OnCheckStateChanged.AddDynamic(this, &UParticipateRow::IsParitcipate);
}

void UParticipateRow::IsParitcipate(bool bIsChecked)
{
	if (CheckBox_Participate->IsChecked())
	{
		for (int i = 0; i < DungeonChoiceWnd->GetMercenaryState()->GetMercenaryActors().Num(); ++i)
		{
			if (DungeonChoiceWnd->GetMercenaryState()->GetMercenaryActors()[i]->GetMercenaryInfo()->MercenaryCode == MercenaryCode)
			{
				AMercenaryCharacter* participateMerecenary = DungeonChoiceWnd->GetMercenaryState()->GetMercenaryActors()[i];
				DungeonChoiceWnd->GetMercenaryState()->ParticipateMerecenary(participateMerecenary);
			}
		}
	}
	else
	{
		for (int i = 0; i < DungeonChoiceWnd->GetMercenaryState()->GetMercenaryActors().Num(); ++i)
		{
			if (DungeonChoiceWnd->GetMercenaryState()->GetMercenaryActors()[i]->GetMercenaryInfo()->MercenaryCode == MercenaryCode)
			{
				AMercenaryCharacter* participateMerecenary = DungeonChoiceWnd->GetMercenaryState()->GetMercenaryActors()[i];
				DungeonChoiceWnd->GetMercenaryState()->UnParticipateMerecenary(participateMerecenary);
			}
		}
	}
}

void UParticipateRow::UpdatePartcipateRow(FMercenaryInfo* mercenaryInfo)
{
	MercenaryCode = mercenaryInfo->MercenaryCode;

	FString contextString;
	FMercenaryInfo* _mercenaryInfo = DT_MercenaryInfo->FindRow<FMercenaryInfo>(mercenaryInfo->MercenaryCode, contextString);
	
	Text_Name->SetText(_mercenaryInfo->MercenaryName);

	UFRGameInstance* gameInst = Cast<UFRGameInstance>(GetGameInstance());

	UTexture2D* itemImage =
		Cast<UTexture2D>(gameInst->GetStreamableManager()->LoadSynchronous(_mercenaryInfo->MercernaryIcon));

	Image_Sprite->SetBrushFromTexture(itemImage);
}
