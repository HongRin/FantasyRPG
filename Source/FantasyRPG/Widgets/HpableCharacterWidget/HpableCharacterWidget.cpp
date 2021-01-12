#include "HpableCharacterWidget.h"
#include "Actors/Characters/BaseCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Structures/Player/PlayerInfo.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/SWidget.h"
#include "Styling/SlateTypes.h"
#include "Slate/SlateBrushAsset.h"


void UHpableCharacterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ProgressBar_HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_HP")));

	Text_Level = Cast<UTextBlock>(GetWidgetFromName("Text_Level"));


}

void UHpableCharacterWidget::InitializeWidget(ABaseCharacter* ownerCharacter)
{
	OwnerCharacter = ownerCharacter;
}

void UHpableCharacterWidget::UpdateHp()
{
	if (!IsValid(OwnerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("HpableCharacterWidget.cpp :: %d LINE :: OwnerCharacter is not valid!"), __LINE__);
		return;
	}

	if (OwnerCharacter->ActorHasTag(TEXT("BsMonster")))
	{

		FPlayerInfo* playerInfo = GetManager(UPlayerManager)->GetPlayerInfo();

	
		LineHp -= playerInfo->Atk;
	

		if (LineHp / LineMaxHp <= 0.0f)
		{
			LineHp = OwnerCharacter->GetMaxHp() / Line;
			HpCount -= 1.0f;
		}

		ProgressBar_HP->SetPercent(LineHp / LineMaxHp);

		if (HpCount == 3.0f)
		{
			ProgressBar_HP->WidgetStyle.BackgroundImage.TintColor = FLinearColor(0.64f, 0.0f, 0.01f, 1.0f);
			ProgressBar_HP->WidgetStyle.FillImage.TintColor = FLinearColor(1.0f, 0.25f, 0.0f, 1.0f);
		}
		else if (HpCount == 2.0f)
		{
			ProgressBar_HP->WidgetStyle.BackgroundImage.TintColor = FLinearColor(0.3f, 0.005f, 0.0f, 1.0f);
			ProgressBar_HP->WidgetStyle.FillImage.TintColor = FLinearColor(0.64f, 0.0f, 0.01f, 1.0f);
		}
		else if (HpCount == 1.0f)
		{
			ProgressBar_HP->WidgetStyle.BackgroundImage.TintColor = FLinearColor(0.135f, 0.002f, 0.0f, 1.0f);
			ProgressBar_HP->WidgetStyle.FillImage.TintColor = FLinearColor(0.3f, 0.005f, 0.0f, 1.0f);
		}
	}
	else
	ProgressBar_HP->SetPercent(OwnerCharacter->GetHp() / OwnerCharacter->GetMaxHp());


}
                                                   
void UHpableCharacterWidget::SetLevelText(int value)
{
	FText Level = FText::FromString(FString(TEXT("LV ")) + FString::FromInt(value));
	Text_Level->SetText(Level);
}

void UHpableCharacterWidget::SetLineHp(float line = 1.0f)
{
	Line = line;
	HpCount = line;
	LineHp = OwnerCharacter->GetMaxHp() / line;
	LineMaxHp = OwnerCharacter->GetMaxHp() / line;
}

