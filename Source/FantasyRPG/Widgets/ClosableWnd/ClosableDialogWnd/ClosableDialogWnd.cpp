#include "ClosableDialogWnd.h"
#include "Actors/Characters/InteractableNpc/InteractableNpc.h"

#include "Components/Button.h"

void UClosableDialogWnd::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	WndSize = FVector2D(1920.0, 1080.0f);

}

void UClosableDialogWnd::SetOwnerNpc(AInteractableNpc* ownerNpc)
{
	OwnerNpc = ownerNpc;

	// â�� �ݾ��� �� ��ȣ�ۿ��� �������� �մϴ�.
	if (IsValid(CloseButton))
		CloseButton->OnClicked.AddDynamic(OwnerNpc, &AInteractableNpc::FinishInteraction);
}

UClosableWnd* UClosableDialogWnd::OpenShop(FName shopID)
{
	return OwnerNpc->OpenShop(this, shopID);
}