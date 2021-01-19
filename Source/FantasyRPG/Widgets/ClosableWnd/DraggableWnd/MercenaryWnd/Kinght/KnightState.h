#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "KnightState.generated.h"

UCLASS()
class FANTASYRPG_API UKnightState : public UUserWidget
{
	GENERATED_BODY()
	

private :
	class UTextBlock* Text_Atk;
	class UTextBlock* Text_Hp;
	class UTextBlock* Text_SkillPercentage;

protected :
	virtual void NativeConstruct() override;

public :
	void UpdateKnightState(FMercenaryInfo* mercenaryInfo);
};
