#include "ButtonList.h"

#include "MRReinforceWnd.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

UButtonList::UButtonList(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{
}

void UButtonList::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name")));
	Button_List = Cast<UButton>(GetWidgetFromName(TEXT("Button_List")));
	
	Button_List->OnClicked.AddDynamic(this, &UButtonList::ReinforceClicked);
}

void UButtonList::InitializeButtonList(FMercenaryInfo* mercenaryInfo)
{
	MercenaryInfo = mercenaryInfo;
	Text_Name->SetText(mercenaryInfo->MercenaryName);
}

void UButtonList::ReinforceClicked()
{
	MRReinforceWnd->OpenReinforceWnd(MercenaryInfo);
}
