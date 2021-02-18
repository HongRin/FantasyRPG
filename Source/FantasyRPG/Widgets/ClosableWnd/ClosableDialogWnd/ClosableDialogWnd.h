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

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Text_Dialog;

protected :
	virtual void NativeOnInitialized() override;

public:
	void SetOwnerNpc(class AInteractableNpc* ownerNpc);

	void UpdateText(FText npcName, FText dialog);

	UFUNCTION(BlueprintCallable)
	class UClosableWnd* OpenShop(FName shopID);
};
