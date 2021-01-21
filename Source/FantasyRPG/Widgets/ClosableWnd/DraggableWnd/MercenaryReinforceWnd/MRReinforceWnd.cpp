#include "MRReinforceWnd.h"

#include "ButtonList.h"

#include "Components/ScrollBox.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"

#include "KnightReinforce/KnightReinforce.h"
#include "HelaerReinforce/HealerReinforce.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Enums/MercenaryType.h"

#include "Engine/DataTable.h"

UMRReinforceWnd::UMRReinforceWnd(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{
	static ConstructorHelpers::FClassFinder<UButtonList> BP_BUTTON_LIST(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryReinforceWnd/BP_ButtonList.BP_ButtonList_C'"));
	if (BP_BUTTON_LIST.Succeeded())  BP_ButtonList = BP_BUTTON_LIST.Class;
	else UE_LOG(LogTemp, Error, TEXT("UMRReinforceWnd.cpp::%d::LINE:: BP_BUTTON_LIST is not loaded"), __LINE__);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryInfo.DT_MercenaryInfo'"));
	if (DT_MERCENARY_INFO.Succeeded()) DT_MercenaryInfo = DT_MERCENARY_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UMRReinforceWnd.cpp::%d::LINE:: DT_MERCENARY_INFO is not loaded"), __LINE__);

	static ConstructorHelpers::FClassFinder<UKnightReinforce> BP_KNIGHT_REINFORCE(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryReinforceWnd/BP_Knight_Reinforce.BP_Knight_Reinforce_C'"));
	if (BP_KNIGHT_REINFORCE.Succeeded()) BP_KnightReinforce = BP_KNIGHT_REINFORCE.Class;
	else UE_LOG(LogTemp, Error, TEXT("UButtonList.cpp::%d::LINE:: BP_KNIGHT_REINFORCE is not loaded"), __LINE__);

	static ConstructorHelpers::FClassFinder<UHealerReinforce> BP_HEALER_REINFORCE(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryReinforceWnd/BP_Helaer_Reinforce.BP_Helaer_Reinforce_C'"));
	if (BP_HEALER_REINFORCE.Succeeded()) BP_HealerReinforce = BP_HEALER_REINFORCE.Class;
	else UE_LOG(LogTemp, Error, TEXT("UButtonList.cpp::%d::LINE:: BP_HEALER_REINFORCE is not loaded"), __LINE__);
}

void UMRReinforceWnd::NativeConstruct()
{
	Super::NativeConstruct();

	ScrollBox_ButtonList = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_ButtonList")));

	MercenaryState = Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn())->GetMercenaryState();

	UpdateWndSize(500, 600);

	InitializeButtonList();
}

void UMRReinforceWnd::InitializeButtonList()
{
	if (MercenaryState->GetScoutMercenarys().Num() == 0) return;

	for (int i = 0; i < MercenaryState->GetScoutMercenarys().Num(); ++i)
	{
		FString contextString;

		FMercenaryInfo* mercenaryInfo = DT_MercenaryInfo->FindRow<FMercenaryInfo>(
			MercenaryState->GetScoutMercenarys()[i].MercenaryCode, contextString);

		UButtonList* buttonList = CreateWidget<UButtonList>(this, BP_ButtonList);
		ScrollBox_ButtonList->AddChild(buttonList);
		buttonList->SetMRReinforceWnd(this);
		buttonList->InitializeButtonList(mercenaryInfo);
	}
}

void UMRReinforceWnd::OpenReinforceWnd(FMercenaryInfo* mercenaryInfo)
{
	if (mercenaryInfo->MercenaryType == EMercenaryType::MCT_KNIGHT)
	{
		UKnightReinforce* knightReinforce = Cast<UKnightReinforce>(CreateChildClosableWnd(BP_KnightReinforce));
	}
	if (mercenaryInfo->MercenaryType == EMercenaryType::MCT_HEALER)
	{
		UHealerReinforce* helaerReinforce = Cast<UHealerReinforce>(CreateChildClosableWnd(BP_HealerReinforce));
	}
}
