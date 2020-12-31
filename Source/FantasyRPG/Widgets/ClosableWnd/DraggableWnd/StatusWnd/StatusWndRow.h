#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/StatusType.h"
#include "StatusWndRow.generated.h"

UCLASS()
class FANTASYRPG_API UStatusWndRow : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY()
	class UStatusWnd* StatusWnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatusType StatusType; 

	UPROPERTY()
	class ARPGPlayerController* PlayerController;

	struct FPlayerInfo* PlayerInfo;

private:
	class UTextBlock* Text_StatInfo;
	class UTextBlock* Text_Stat;
	class UButton* Button_Addition;

protected:
	virtual void NativeOnInitialized() override;

private :
	void UpdateRow();

	// 스탯을 찍었을 때 호출되는 메서드
	UFUNCTION()
	void OnStatPlusButtuonClicked();

public :
	FORCEINLINE void SetStatusWnd(class UStatusWnd* statusWnd)
	{
		StatusWnd = statusWnd;
	}

};