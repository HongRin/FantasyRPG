#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "MercenaryHpRow.generated.h"

UCLASS()
class FANTASYRPG_API UMercenaryHpRow : public UUserWidget
{
	GENERATED_BODY()

private :
	class AMercenaryCharacter* MercenaryCharacter;
	class UTextBlock* Text_Name;
	class UProgressBar* ProgressBar_Hp;
	class UMercenaryHpWnd* MercenaryHpWnd;

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeMercenaryHpRow(FMercenaryInfo* mercenaryInfo);
	
	void UpdateMercenaryHp();

	FORCEINLINE void SetMercenaryHpWnd(class UMercenaryHpWnd* mercenaryHpWnd)
	{
		MercenaryHpWnd = mercenaryHpWnd;
	}
};
