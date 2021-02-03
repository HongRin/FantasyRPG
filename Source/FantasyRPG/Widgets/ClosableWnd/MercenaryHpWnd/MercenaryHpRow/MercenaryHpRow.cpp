#include "MercenaryHpRow.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "Widgets/ClosableWnd/MercenaryHpWnd/MercenaryHpWnd.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

void UMercenaryHpRow::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));
	ProgressBar_Hp = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Hp")));
}

void UMercenaryHpRow::InitializeMercenaryHpRow(FMercenaryInfo* mercenaryInfo)
{
	Text_Name->SetText(mercenaryInfo->MercenaryName);

	UMercenaryStateComponent* mercenaryState = Cast<APlayerCharacter>(GetManager(UPlayerManager)->
		GetPlayerController()->GetPawn())->GetMercenaryState();
	
	for (int i = 0; i < mercenaryState->GetMercenaryActors().Num(); ++i)
	{
		if (mercenaryInfo->MercenaryCode == mercenaryState->GetMercenaryActors()[i]->GetMercenaryInfo()->MercenaryCode)
		{
			MercenaryCharacter = mercenaryState->GetMercenaryActors()[i];
		}
	}

	ProgressBar_Hp->SetPercent(MercenaryCharacter->GetHp() / MercenaryCharacter->GetMaxHp());
	
	MercenaryHpWnd->OnTakeDamageEvent.AddUObject(this, &UMercenaryHpRow::UpdateMercenaryHp);

}

void UMercenaryHpRow::UpdateMercenaryHp()
{
	ProgressBar_Hp->SetPercent(MercenaryCharacter->GetHp() / MercenaryCharacter->GetMaxHp());
}
