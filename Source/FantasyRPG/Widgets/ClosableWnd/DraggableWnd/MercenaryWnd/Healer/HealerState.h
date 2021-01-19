// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "HealerState.generated.h"

UCLASS()
class FANTASYRPG_API UHealerState : public UUserWidget
{
	GENERATED_BODY()

private:
	class UTextBlock* Text_SkillCooldown;
	class UTextBlock* Text_BuffFigure;
	class UTextBlock* Text_HealingFigure;
	class UTextBlock* Text_Hp;
	class UTextBlock* Text_SkillPercentage;

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHealerState(FMercenaryInfo* mercenaryInfo);
	
};
