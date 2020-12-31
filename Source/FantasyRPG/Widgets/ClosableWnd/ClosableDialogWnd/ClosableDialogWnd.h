#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/ClosableWnd.h"
#include "ClosableDialogWnd.generated.h"

UCLASS()
class FANTASYRPG_API UClosableDialogWnd : public UClosableWnd
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class AInteractableNpc* OwnerNpc;

protected :
	virtual void NativeOnInitialized() override;

public:
	void SetOwnerNpc(class AInteractableNpc* ownerNpc);

	UFUNCTION(BlueprintCallable)
	class UClosableWnd* OpenShop(FName shopID);
};
