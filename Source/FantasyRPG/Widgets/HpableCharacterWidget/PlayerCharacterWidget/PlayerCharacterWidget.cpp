#include "PlayerCharacterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "Widgets/ClosableWnd/MercenaryHpWnd/MercenaryHpWnd.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"

#include "Components/TextBlock.h"

void UPlayerCharacterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ProgressBar_HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_HP")));
	Canvas_ClosableWnds = Cast<UCanvasPanel>(GetWidgetFromName("Canvas_ClosableWnds"));
	BP_MercenaryHpWnd = Cast<UMercenaryHpWnd>(GetWidgetFromName("BP_MercenaryHpWnd"));

	SetDesiredSizeInViewport(FVector2D(1920.0f, 1080.0f));
}

void UPlayerCharacterWidget::AddClosableWnd(UClosableWnd* closableWnd)
{
	Canvas_ClosableWnds->AddChild(closableWnd);

	Cast<UCanvasPanelSlot>(closableWnd->Slot)->SetSize(closableWnd->WndSize);

	if (closableWnd->onWndOpened.IsBound())
		closableWnd->onWndOpened.Broadcast();
}

void UPlayerCharacterWidget::RemoveClosableWnd(UClosableWnd* closableWnd)
{
	closableWnd->RemoveFromParent();

	if (closableWnd->onWndClosed.IsBound())
		closableWnd->onWndClosed.Broadcast();
}
