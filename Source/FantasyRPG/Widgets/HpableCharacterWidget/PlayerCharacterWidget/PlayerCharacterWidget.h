#pragma once

#include "CoreMinimal.h"
#include "Widgets/HpableCharacterWidget/HpableCharacterWidget.h"
#include "PlayerCharacterWidget.generated.h"

UCLASS()
class FANTASYRPG_API UPlayerCharacterWidget : public UHpableCharacterWidget
{
	GENERATED_BODY()

private:
	class UCanvasPanel* Canvas_ClosableWnds;
	class UMercenaryHpWnd* BP_MercenaryHpWnd;
	class UProgressBar* ProgressBar_HP;

protected:
	virtual void NativeOnInitialized() override;

public:
	void AddClosableWnd(class UClosableWnd* closableWnd);

	void RemoveClosableWnd(class UClosableWnd* closableWnd);

	FORCEINLINE class UCanvasPanel* GetClosableWnds() const
	{
		return Canvas_ClosableWnds;
	}

	FORCEINLINE class UMercenaryHpWnd* GetMercenaryHpWnd() const
	{
		return BP_MercenaryHpWnd;
	}

};
