#include "ReinforceWndRow.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Components/PlayerInventory/PlayerInventoryComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Enums/ReinforceResult.h"

#include "Structures/EquipItem/EquipItemInfo.h"

#include "Widgets/ClosableWnd/DraggableWnd/ReinforceWnd/ReinforceWnd.h"

#include "Engine/DataTable.h"

UReinforceWndRow::UReinforceWndRow(const FObjectInitializer& objInitializer) :
	Super(objInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EQUIP_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_EquipItemInfo.DT_EquipItemInfo'"));

	if (DT_EQUIP_ITEM_INFO.Succeeded())
	{
		DTEquipItemInfo = DT_EQUIP_ITEM_INFO.Object;
		{ UE_LOG(LogTemp, Warning, TEXT("ReinforceWndRow.cpp :: %d LINE :: DT_EQUIP_ITEM_INFO is loaded!"), __LINE__); }
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ReinforceWndRow.cpp :: %d LINE :: DT_EQUIP_ITEM_INFO is not loaded!"), __LINE__);
	}
}

void UReinforceWndRow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_AdditionalInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_AdditionalInfo")));
	Text_AdditionalInfo->TextDelegate.BindDynamic(this, &UReinforceWndRow::UpdateAddtionalInfoText);

	Text_Type = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Type")));
	Text_Level = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Level")));
	Text_Probability = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Probability")));
	Text_Costs = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Costs")));
	Text_Additional = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Additional")));
	Button_Reinforce = Cast<UButton>(GetWidgetFromName(TEXT("Button_Reinforce")));
	Button_Reinforce->OnClicked.AddDynamic(this, &UReinforceWndRow::OnReinforceButtonClicked);

	UPlayerManager* playerManager = Cast<UFRGameInstance>(GetGameInstance())->GetManagerClass<UPlayerManager>();
	PlayerCharacter = Cast<APlayerCharacter>(playerManager->GetPlayerController()->GetPawn());
	PlayerInventory = PlayerCharacter->GetPlayerInventory();

	UpdateRow();
}

void UReinforceWndRow::UpdateRow()
{
	FName itemCode = PlayerInventory->GetEquipItemCode(ItemType);

	FString contextString;
	auto equipItemInfo = *DTEquipItemInfo->FindRow<FEquipItemInfo>(
		itemCode, contextString);

	auto nextItemInfo = (equipItemInfo.bMaximumLevel) ?
		FEquipItemInfo() :
		*DTEquipItemInfo->FindRow<FEquipItemInfo>(
			equipItemInfo.NextReinforcementItemCode, contextString);


#pragma region Item Type Text Setting
	FText itemTypeText = FText();

	switch (equipItemInfo.ItemType)
	{
	case EEquipItemType::EI_Weapon :  itemTypeText = FText::FromString(TEXT("무기"));	
		break;
	case EEquipItemType::EI_Armor  :  itemTypeText = FText::FromString(TEXT("방어구"));	
		break;
	}

	Text_Type->SetText(itemTypeText);

#pragma endregion

#pragma region Item Level Text Setting
	FText itemLevelText = (equipItemInfo.bMaximumLevel) ?
		FText::FromString(TEXT("MAX")) :
		FText::FromString(
			FString(TEXT("LV ")) +
			FString::FromInt(equipItemInfo.ItemLevel) +
			FString(TEXT(" -> ")) +
			FString::FromInt(nextItemInfo.ItemLevel));

	Text_Level->SetText(itemLevelText);
#pragma endregion

#pragma region Item Probability Text Setting
	FText itemProbabilityText = (equipItemInfo.bMaximumLevel) ?
		FText() : FText::FromString(
			FString::Printf(TEXT("%.2f%%"), nextItemInfo.ReinforcementProbability));

	Text_Probability->SetText(itemProbabilityText);
#pragma endregion

#pragma region Item Costs Text Setting
	FText itemReinforceCostsText = (equipItemInfo.bMaximumLevel) ?
		FText() : FText::FromString(FString::FromInt(nextItemInfo.ReinforcementCosts));

	Text_Costs->SetText(itemReinforceCostsText);
#pragma endregion

#pragma region Item Additional Text Setting
	switch (equipItemInfo.ItemType)
	{
	case EEquipItemType::EI_Weapon: 
		Text_Additional->SetText(
		FText::FromString(
				FString::Printf(TEXT("%.1f"), nextItemInfo.AdditionalOffensiveForce) +
				FString(TEXT(" -> ")) +
				FString::Printf(TEXT("%.1f"), nextItemInfo.AdditionalOffensiveForce)));
		break;
	case EEquipItemType::EI_Armor:  
		Text_Additional->SetText(
		FText::FromString(
			FString::Printf(TEXT("%.1f"), nextItemInfo.AdditionalDefensiveForce) +
			FString(TEXT(" -> ")) +
			FString::Printf(TEXT("%.1f"), nextItemInfo.AdditionalDefensiveForce)));
		break;
	}
#pragma endregion

#pragma region Button Setting
	// 현재 장착중인 아이템이 최대 레벨이라면 버튼을 비활성화 시킵니다.
	Button_Reinforce->SetIsEnabled(!equipItemInfo.bMaximumLevel);
#pragma endregion
}

void UReinforceWndRow::OnReinforceButtonClicked()
{
	EReinforceResult reinforceResult = PlayerInventory->TryReinforce(ItemType);

	switch (reinforceResult)
	{
	case EReinforceResult::RF_Success:
		UpdateRow();
		PlayerCharacter->UpdateEquipItemState(false, ItemType);
		break;

	case EReinforceResult::RF_LackOfMonemy:
	break;

	case EReinforceResult::RF_Fail:
		UE_LOG(LogTemp, Warning, TEXT("Fail !!!!!"));
		break;
	}
}
