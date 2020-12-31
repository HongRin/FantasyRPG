#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"
#include "Enums/EquipItemType.h"
#include "ReinforceWndRow.generated.h"

UCLASS()
class FANTASYRPG_API UReinforceWndRow : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY()
	class UReinforceWnd* ReinforceWnd;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	class UPlayerInventoryComponent* PlayerInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipItemType ItemType;

private :
	class UTextBlock* Text_AdditionalInfo;
	class UTextBlock* Text_Type;
	class UTextBlock* Text_Level;
	class UTextBlock* Text_Probability;
	class UTextBlock* Text_Costs;
	class UTextBlock* Text_Additional;

	class UButton* Button_Reinforce;

	class UDataTable* DTEquipItemInfo;

public :
	UReinforceWndRow(const FObjectInitializer& objInitializer);

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ReinforceRow Additional Info")
	FText AdditionalInfoText;

protected :
	virtual void NativeOnInitialized() override;

private:
	// 행을 갱신합니다.
	void UpdateRow();

	// 강화 버튼을 눌렀을 때 호출될 메서드
	UFUNCTION()
	void OnReinforceButtonClicked();

public:
	FORCEINLINE void SetReinforceWnd(class UReinforceWnd* reinfoceWnd)
	{
		ReinforceWnd = reinfoceWnd;
	}

	UFUNCTION()
	FORCEINLINE FText UpdateAddtionalInfoText()
	{ return AdditionalInfoText; }
	
};
