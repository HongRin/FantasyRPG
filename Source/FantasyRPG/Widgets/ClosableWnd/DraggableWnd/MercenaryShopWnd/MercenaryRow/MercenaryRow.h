#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "MercenaryRow.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryRow : public UUserWidget
{
	GENERATED_BODY()
	
private :
	class UDataTable* DT_MercenaryInfo;
	class UMercenaryShopWnd* MercenaryShopWnd;

	class UTextBlock* Text_Name;
	class UTextBlock* Text_Costs;
	class UButton* Button_Scout;

	class UMercenaryStateComponent* MercenaryState;
	
	FMercenaryInfo* MercenaryInfo;

public :
	UMercenaryRow(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void UpdateMercenaryRow(FMercenaryInfo* mercenaryInfo);

private :
	UFUNCTION()
	void OnScoutButtonClicked();

public :
	FORCEINLINE void SetMercenaryShopWnd(class UMercenaryShopWnd* mercenaryShopWnd)
	{
		MercenaryShopWnd = mercenaryShopWnd;
	}
};
