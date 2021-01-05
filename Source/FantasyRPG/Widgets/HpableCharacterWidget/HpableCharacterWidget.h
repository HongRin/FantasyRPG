#pragma once

#include "CoreMinimal.h"
#include "Widgets/CharacterWidget.h"
#include "HpableCharacterWidget.generated.h"

UCLASS()
class FANTASYRPG_API UHpableCharacterWidget : public UCharacterWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class ABaseCharacter* OwnerCharacter;

	class UProgressBar* ProgressBar_HP;

	class UTextBlock* Text_Level;

	float LineHp;
	float LineMaxHp;

protected:
	virtual void NativeOnInitialized() override;

public:
	void InitializeWidget(class ABaseCharacter* ownerCharacter);
	void UpdateHp();
	void SetLevelText(int value);
	void SetLineHp(float Line);
	
};
