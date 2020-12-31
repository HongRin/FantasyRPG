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

	// 창을 닫았을 때 상호작용이 끝나도록 합니다.
	if (IsValid(CloseButton))
		CloseButton->OnClicked.AddDynamic(OwnerNpc, &AInteractableNpc::FinishInteraction);
}

UClosableWnd* UClosableDialogWnd::OpenShop(FName shopID)
{
	return OwnerNpc->OpenShop(this, shopID);
}