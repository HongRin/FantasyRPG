#include "MercenaryShopWnd.h"
#include "MercenaryRow/MercenaryRow.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/ScrollBox.h"
#include "Engine/DataTable.h"

UMercenaryShopWnd::UMercenaryShopWnd(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{
	static ConstructorHelpers::FClassFinder<UMercenaryRow> BP_MERCENARY_ROW(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryShopWnd/BP_MercenaryRow.BP_MercenaryRow_C'"));
	if (BP_MERCENARY_ROW.Succeeded()) BP_MercenaryRow = BP_MERCENARY_ROW.Class;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryShopWnd.cpp::%d::LINE::BP_MERCENARY_ROW is not loaded! "));

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryInfo.DT_MercenaryInfo'"));
	if (DT_MERCENARY_INFO.Succeeded()) DT_MercenaryInfo = DT_MERCENARY_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryShopWnd.cpp::%d::LINE::BP_MERCENARY_ROW is not loaded! "));
}

void UMercenaryShopWnd::NativeConstruct()
{
	Super::NativeConstruct();

	ScrollBox_MercenaryList = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_MercenaryList")));

	MercenaryState = Cast<APlayerCharacter>(GetManager(UPlayerManager)->
		GetPlayerController()->GetPawn())->GetMercenaryState();

	UpdateWndSize(700.0f, 600.0f);
}

void UMercenaryShopWnd::InitializeMercenaryShopWnd(TArray<FShopItemInfo> saleItems)
{
	FString contextString;

	if (MercenaryState->GetScoutMercenarys().Num() == 2) return;

	for (int i = 0; i < saleItems.Num(); ++i)
	{
		FMercenaryInfo* mercenaryInfo = DT_MercenaryInfo->FindRow<FMercenaryInfo>(saleItems[i].ItemCode,
			contextString);

		UE_LOG(LogTemp, Warning, TEXT("i :: %d"), i);
		
		if (MercenaryState->GetScoutMercenarys().Num() != 0)
		{
			for (int j = 0; j < MercenaryState->GetScoutMercenarys().Num(); ++j)
			{
				if (saleItems[i].ItemCode == MercenaryState->GetScoutMercenarys()[j].MercenaryCode) break;

				UMercenaryRow* mercenaryRow = CreateWidget<UMercenaryRow>(this, BP_MercenaryRow);

				mercenaryRow->SetMercenaryShopWnd(this);

				ScrollBox_MercenaryList->AddChild(mercenaryRow);

				mercenaryRow->UpdateMercenaryRow(mercenaryInfo);
			}
		}
		else
		{
			UMercenaryRow* mercenaryRow = CreateWidget<UMercenaryRow>(this, BP_MercenaryRow);

			mercenaryRow->SetMercenaryShopWnd(this);

			ScrollBox_MercenaryList->AddChild(mercenaryRow);

			mercenaryRow->UpdateMercenaryRow(mercenaryInfo);
		}
	}
}
