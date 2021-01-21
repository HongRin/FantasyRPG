#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "ButtonList.generated.h"

UCLASS()
class FANTASYRPG_API UButtonList : public UUserWidget
{
	GENERATED_BODY()



private :
	class UMRReinforceWnd* MRReinforceWnd;
	class UTextBlock* Text_Name;
	class UButton* Button_List;
	
	FMercenaryInfo* MercenaryInfo;

public :
	UButtonList(const FObjectInitializer& ObjInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeButtonList(FMercenaryInfo* mercenaryInfo);
	
private :
	UFUNCTION()
	void ReinforceClicked();

public :
	FORCEINLINE void SetMRReinforceWnd(UMRReinforceWnd* mrReinforceWnd)
	{
		MRReinforceWnd = mrReinforceWnd;
	}
};
