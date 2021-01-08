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
	UpdateHp();
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
		ProgressBar_HP->WidgetStyle.BackgroundImage.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		ProgressBar_HP->WidgetStyle.FillImage.TintColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
		UE_LOG(LogTemp, Warning, TEXT("HP : %.2f"), LineHp);
		UE_LOG(LogTemp, Warning, TEXT("LINEHP : %.2f"), LineMaxHp);
		UE_LOG(LogTemp, Warning, TEXT("Perecent : %.2f"), LineHp / LineMaxHp);
	
		LineHp -= playerInfo->Atk;
	
		if (LineHp / LineMaxHp <= 0.0f)
		{
			LineHp = OwnerCharacter->GetMaxHp() / Line;
			--HpCount;
		}
	
		ProgressBar_HP->SetPercent(LineHp / LineMaxHp);
	}
	else
	ProgressBar_HP->SetPercent(OwnerCharacter->GetHp() / OwnerCharacter->GetMaxHp());
}
                                                   
void UHpableCharacterWidget::SetLevelText(int value)
{
	FText Level = FText::FromString(FString(TEXT("LV ")) + FString::FromInt(value));
	Text_Level->SetText(Level);
}

void UHpableCharacterWidget::SetLineHp(float line)
{
	Line = line;
	HpCount = line;
	LineHp = OwnerCharacter->GetMaxHp() / line;
	LineMaxHp = OwnerCharacter->GetMaxHp() / line;
}

