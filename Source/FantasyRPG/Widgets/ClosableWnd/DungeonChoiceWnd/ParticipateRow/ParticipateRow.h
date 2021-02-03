#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "ParticipateRow.generated.h"

UCLASS()
class FANTASYRPG_API UParticipateRow : public UUserWidget
{
	GENERATED_BODY()

private:
	class UDataTable* DT_MercenaryInfo;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Sprite;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CheckBox_Participate;

	class UDungeonChoiceWnd* DungeonChoiceWnd;

	FName MercenaryCode;

public:
	UParticipateRow(const FObjectInitializer& objInitializer);

protected:
	void NativeConstruct() override;

private :
	UFUNCTION()
	void IsParitcipate(bool bIsChecked);

public:
	void UpdatePartcipateRow(FMercenaryInfo* mercenaryInfo);

	FORCEINLINE void SetDungeonChoiceWnd(class UDungeonChoiceWnd* dungeonChoiceWnd)
	{
		DungeonChoiceWnd = dungeonChoiceWnd;
	}
};
