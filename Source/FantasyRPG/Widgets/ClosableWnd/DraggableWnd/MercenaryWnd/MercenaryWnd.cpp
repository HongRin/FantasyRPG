#include "MercenaryWnd.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"
#include "Components/ScrollBox.h"

#include "Enums/MercenaryType.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Structures/MercenarySlotInfo/MercenarySlotInfo.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"

#include "Healer/HealerState.h"
#include "Kinght/KnightState.h"


UMercenaryWnd::UMercenaryWnd(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{
	static ConstructorHelpers::FClassFinder<UHealerState> BP_HEALER_STATE(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryWnd/BP_HealerMercenary.BP_HealerMercenary_C'"));
	if (BP_HEALER_STATE.Succeeded()) BP_HealerState = BP_HEALER_STATE.Class;
	else UE_LOG(LogTemp, Warning, TEXT("UMercenaryWnd.cpp::%d::LINE:: BP_HEALER_STATE is not loaded"), __LINE__);

	static ConstructorHelpers::FClassFinder<UKnightState> BP_KNIGHT_STATE(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryWnd/BP_KnightMercenary.BP_KnightMercenary_C'"));
	if (BP_KNIGHT_STATE.Succeeded()) BP_KnightState = BP_KNIGHT_STATE.Class;
	else UE_LOG(LogTemp, Warning, TEXT("UMercenaryWnd.cpp::%d::LINE:: BP_KNIGHT_STATE is not loaded"), __LINE__);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryInfo.DT_MercenaryInfo'"));
	if (DT_MERCENARY_INFO.Succeeded()) DT_MercenaryInfo = DT_MERCENARY_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryShopWnd.cpp::%d::LINE::BP_MERCENARY_ROW is not loaded! "));
}

void UMercenaryWnd::NativeConstruct()
{
	Super::NativeConstruct();

	ScrollBox_MercenaryList = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_MercenaryList")));

	MercenaryState = Cast<APlayerCharacter>(GetManager(UPlayerManager)->
		GetPlayerController()->GetPawn())->GetMercenaryState();

	UpdateWndSize(700.0f, 600.0f);
}

void UMercenaryWnd::InitializeMercenaryWnd()
{
	if (MercenaryState->GetMercenaryActors().Num() == 0) return;
	for (int i = 0; i < MercenaryState->GetMercenaryActors().Num(); ++i)
	{
		FString contextString;
		FMercenaryInfo* mercenaryInfo = MercenaryState->GetMercenaryActors()[i]->GetMercenaryInfo();

		if (mercenaryInfo->MercenaryType == EMercenaryType::MCT_HEALER)
		{
			UHealerState* helaerState = CreateWidget<UHealerState>(this, BP_HealerState);
			
			ScrollBox_MercenaryList->AddChild(helaerState);

			helaerState->UpdateHealerState(mercenaryInfo);
		}
		else if (mercenaryInfo->MercenaryType == EMercenaryType::MCT_KNIGHT)
		{
			UKnightState* knightState = CreateWidget<UKnightState>(this, BP_KnightState);
			
			ScrollBox_MercenaryList->AddChild(knightState);

			knightState->UpdateKnightState(mercenaryInfo);
		}
	}
}
