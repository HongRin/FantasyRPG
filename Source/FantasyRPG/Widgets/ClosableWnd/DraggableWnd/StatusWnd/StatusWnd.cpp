#include "StatusWnd.h"
#include "StatusWndRow.h"
#include "Components/TextBlock.h"


void UStatusWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Text_StatPoint = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_StatPoint")));

	Cast<UStatusWndRow>(GetWidgetFromName(TEXT("BP_StatusRow_Atk")))->SetStatusWnd(this);
	Cast<UStatusWndRow>(GetWidgetFromName(TEXT("BP_StatusRow_Def")))->SetStatusWnd(this);
	Cast<UStatusWndRow>(GetWidgetFromName(TEXT("BP_StatusRow_HP")))->SetStatusWnd(this);
	Cast<UStatusWndRow>(GetWidgetFromName(TEXT("BP_StatusRow_MP")))->SetStatusWnd(this);

	UpdateWndSize(500.0f, 350.0f);
}

void UStatusWnd::UpdateStatPointText(FText text)
{
	Text_StatPoint->SetText(text);
}
