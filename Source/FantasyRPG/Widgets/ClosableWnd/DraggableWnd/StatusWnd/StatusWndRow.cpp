#include "StatusWndRow.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Widgets/HpableCharacterWidget/PlayerCharacterWidget/PlayerCharacterWidget.h"
#include "Components/PlayerWndController/PlayerWndControllerComponent.h"
#include "StatusWnd.h"
#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Structures/Player/PlayerInfo.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UStatusWndRow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_StatInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_StatInfo")));
	Text_Stat = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Stat")));
	Button_Addition = Cast<UButton>(GetWidgetFromName(TEXT("Button_StatAddition")));

	PlayerController = (GetManager(UPlayerManager)->GetPlayerController());
	PlayerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	Button_Addition->OnClicked.AddDynamic(this, &UStatusWndRow::OnStatPlusButtuonClicked);

	UpdateRow();
}

void UStatusWndRow::UpdateRow()
{
	switch (StatusType)
	{
	case EStatusType::ST_Atk : 
		Text_StatInfo->SetText(FText::FromString(TEXT("ATK")));
		Text_Stat->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), PlayerInfo->Atk)));
		break;
	case EStatusType::ST_Def:
		Text_StatInfo->SetText(FText::FromString(TEXT("DEF")));
		Text_Stat->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), PlayerInfo->Def)));
		break;
	case EStatusType::ST_Hp:
		Text_StatInfo->SetText(FText::FromString(TEXT("HP")));
		Text_Stat->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), PlayerInfo->MaxHp)));
		break;
	case EStatusType::ST_Mp:
		Text_StatInfo->SetText(FText::FromString(TEXT("MP")));
		Text_Stat->SetText(FText::FromString(FString::Printf(TEXT("%.1f%"), PlayerInfo->MaxMp)));
		break;
	}
}

void UStatusWndRow::OnStatPlusButtuonClicked()
{
	if (PlayerInfo->StatPoint == 0) return;

	switch (StatusType)
	{
	case EStatusType::ST_Atk:
		PlayerInfo->Atk += 3;
		break;
	case EStatusType::ST_Def:
		PlayerInfo->Def += 3;
		break;
	case EStatusType::ST_Hp:
		PlayerInfo->MaxHp += 20;
		PlayerController->GetPlayerCharacterWidgetInstance()->UpdateHp();
		break;
	case EStatusType::ST_Mp:
		PlayerInfo->MaxMp += 20;
		break;
	}

	PlayerInfo->StatPoint--;

	if (StatusWnd != nullptr)
	{
		StatusWnd->UpdateStatPointText(FText::FromString(FString::FromInt(PlayerInfo->StatPoint)));
	}

	UpdateRow();
}
