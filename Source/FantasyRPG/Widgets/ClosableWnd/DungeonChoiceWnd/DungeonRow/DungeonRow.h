#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"
#include "DungeonRow.generated.h"

UCLASS()
class FANTASYRPG_API UDungeonRow : public UUserWidget
{
	GENERATED_BODY()
	
private :
	class UDataTable* DT_DungeonRowInfo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_DungeonSprite;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_EnterDungeon;

	FName NextDungeonName;

public :
	UDungeonRow(const FObjectInitializer& ObjectInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeDungeonRow(FName dungeonCode);

private :
	UFUNCTION()
		void ClickEnterDungeonButton();
};
