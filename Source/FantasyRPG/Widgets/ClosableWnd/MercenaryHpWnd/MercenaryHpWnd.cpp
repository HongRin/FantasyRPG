#include "MercenaryHpWnd.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"
#include "Components/VerticalBox.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "MercenaryHpRow/MercenaryHpRow.h"

UMercenaryHpWnd::UMercenaryHpWnd()
{
	static ConstructorHelpers::FClassFinder<UMercenaryHpRow> BP_MERCENARY_HP_ROW
		(TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/Mercenary/BP_MercenaryHpRow.BP_MercenaryHpRow_C'"));
	if (BP_MERCENARY_HP_ROW.Succeeded()) BP_MercenaryHpRow = BP_MERCENARY_HP_ROW.Class;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryHpWnd.cpp::%d::LINE:: BP_MERCENARY_HP_ROW is not loaded! "), __LINE__);
}

void UMercenaryHpWnd::NativeConstruct()
{
	Super::NativeConstruct();

	VerticalBox_List = Cast<UVerticalBox>(GetWidgetFromName(TEXT("VerticalBox_List")));

	MercenaryState = Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn())->GetMercenaryState();
}

void UMercenaryHpWnd::AddMercenaryHpList(FMercenaryInfo* mercenaryInfo)
{
	UMercenaryHpRow* mercenaryHpRow = CreateWidget<UMercenaryHpRow>(this, BP_MercenaryHpRow);

	VerticalBox_List->AddChild(mercenaryHpRow);
	mercenaryHpRow->SetMercenaryHpWnd(this);
	mercenaryHpRow->InitializeMercenaryHpRow(mercenaryInfo);
}
