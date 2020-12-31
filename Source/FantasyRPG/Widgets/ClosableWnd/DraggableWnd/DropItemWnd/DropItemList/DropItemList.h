#pragma once

#include "FantasyRPG.h"
#include "Blueprint/UserWidget.h"
#include "DropItemList.generated.h"

UCLASS()
class FANTASYRPG_API UDropItemList : public UUserWidget
{
	GENERATED_BODY()

private:
	class UDataTable* DT_ItemInfo;

	FName ItemCode;
	int32 ItemCount;

private:
	class UImage* Image_ItemSprite;
	class UTextBlock* Text_ItemCount;
	class UTextBlock* Text_ItemName;
	class UButton* Button_SlotClickEvent;
	class UBorder* Border_SlotClickEvent;

public:
	UDropItemList(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

private :
	UFUNCTION()
	FEventReply ItemDrop(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

public:
	void InitializeDropItem(FName itemCode, int32 itemCount);
};
