#include "DungeonChoiceWnd.h"

#include "Components/Button.h"

void UDungeonChoiceWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Cancel = Cast<UButton>(GetWidgetFromName(TEXT("Button_Cancel")));

	UpdateWndSize(1920.0f, 1080.0f);

	Button_Cancel->OnClicked.AddDynamic(this, &UClosableWnd::OnCloseButtonClicked);
}
