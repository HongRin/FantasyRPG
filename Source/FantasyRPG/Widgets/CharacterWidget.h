#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

UCLASS()
class FANTASYRPG_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	class UTextBlock* Text_Name;

protected:
	virtual void NativeOnInitialized() override;

public:
	void SetNameText(FText value);
};
