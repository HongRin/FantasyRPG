#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"
#include "MercenaryRow.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryRow : public UUserWidget
{
	GENERATED_BODY()
	
private :
	class UDataTable* DT_MercenaryInfo;

	class UTextBlock* Text_Name;
	class UTextBlock* Text_Costs;
	class UButton* Button_Scout;

public :
	UMercenaryRow(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void UpdateMercenaryRow(FName mercenaryCode);

private :
	UFUNCTION()
	void OnScoutButtonClicked();
};
