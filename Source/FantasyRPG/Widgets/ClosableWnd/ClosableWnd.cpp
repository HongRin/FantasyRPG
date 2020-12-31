#include "ClosableWnd.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"

void UClosableWnd::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateWndSize(1920.0f, 1080.0f);

	SetCloseButton(Cast<UButton>(GetWidgetFromName(TEXT("Button_Close"))));
}

void UClosableWnd::SetCloseButton(UButton* closeButton)
{
	if (!IsValid(closeButton)) return;


	CloseButton = closeButton;
	CloseButton->OnClicked.AddDynamic(this, &UClosableWnd::OnCloseButtonClicked);
}

UClosableWnd* UClosableWnd::CreateChildClosableWnd(TSubclassOf<UClosableWnd> closableWnd)
{
	if (ClosableWndController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ClosableWndController is nullptr"));
		return nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ClosableWndController is not nullptr"));
	}

	// �ڽ� â�� �����մϴ�.
	UClosableWnd* childWnd = ClosableWndController->AddWnd<UClosableWnd>(closableWnd);

	// ������ �ڽ� â�� �θ� â�� �ڽ����� �����մϴ�.
	childWnd->ParentWnd = this;

	// �迭�� �߰��մϴ�.
	ChildWnds.Add(childWnd);

	return childWnd;
}

bool UClosableWnd::IsAllocated(UClosableWnd* childwnd)
{
	return ClosableWndController->IsAllocated(childwnd);
}

void UClosableWnd::RemoveFromParentWnd(UClosableWnd* childWnd)
{
	ChildWnds.Remove(childWnd);
}

void UClosableWnd::OnCloseButtonClicked()
{
	// �θ� â�� �����Ѵٸ�
	if (IsValid(ParentWnd))
	{
		// �ڽ��� �θ� â���� ���ܽ�ŵ�ϴ�.
		ParentWnd->RemoveFromParentWnd(this);
	}

	// ��� �ڽ� â�� �����մϴ�.
	for (auto childWnd : ChildWnds)
	{
		childWnd->OnCloseButtonClicked();

		ClosableWndController->CloseWnd(
			/*bAllClose :					*/	false,
			/*closableWndInstanceToClose :	*/	childWnd);
	}

	ChildWnds.Empty();

	ClosableWndController->CloseWnd(
		/*bAllClose :					*/	false,
		/*closableWndInstanceToClose :	*/	this);
}

void UClosableWnd::UpdateWndSize(float width, float height)
{
	WndSize = FVector2D(width, height);

	Cast<UCanvasPanelSlot>(Slot)->SetSize(WndSize);
	Cast<UCanvasPanelSlot>(Slot)->SetPosition(Cast<UCanvasPanelSlot>(Slot)->GetPosition() +
		(FVector2D(960.0f, 540.0f) - (Cast<UCanvasPanelSlot>(Slot)->GetSize() * 0.5f)));
}
