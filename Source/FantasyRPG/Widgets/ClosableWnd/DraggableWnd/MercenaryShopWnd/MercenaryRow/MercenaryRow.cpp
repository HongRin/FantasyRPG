#include "MercenaryRow.h"
#include "Engine/DataTable.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"

#include "Structures/MercenaryInfo/MercenaryInfo.h"

#include "Widgets/ClosableWnd/DraggableWnd/MercenaryShopWnd/MercenaryShopWnd.h"
#include "Widgets/HpableCharacterWidget/PlayerCharacterWidget/PlayerCharacterWidget.h"
#include "Widgets/ClosableWnd/MercenaryHpWnd/MercenaryHpWnd.h"

UMercenaryRow::UMercenaryRow(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{

}

void UMercenaryRow::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Name    = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name"))); 
	Text_Costs   = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Costs")));
	Button_Scout = Cast<UButton>(GetWidgetFromName(TEXT("Button_Scout")));

	MercenaryState = Cast<APlayerCharacter>(GetManager(UPlayerManager)->
		GetPlayerController()->GetPawn())->GetMercenaryState();

	Button_Scout->OnClicked.AddDynamic(this, &UMercenaryRow::OnScoutButtonClicked);
}

void UMercenaryRow::UpdateMercenaryRow(FMercenaryInfo* mercenaryInfo)
{
	MercenaryInfo = mercenaryInfo;
	Text_Name->SetText(mercenaryInfo->MercenaryName);
	Text_Costs->SetText(FText::FromString(FString::FromInt(mercenaryInfo->Cost)));
}

void UMercenaryRow::OnScoutButtonClicked()
{
	MercenaryState->ScoutMercenary(MercenaryInfo->MercenaryCode);
	RemoveFromParent();
}
