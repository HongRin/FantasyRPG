#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "CharacterWidgetComponent.generated.h"

UCLASS()
class FANTASYRPG_API UCharacterWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxDrawableDistance;

	UPROPERTY()
		class UCameraComponent* PlayerCamera;

public:
	UCharacterWidgetComponent();

public:
	virtual void TickComponent(
		float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void DistanceToggle();

public:
	void InitializeCharaterWidget(
		TSubclassOf<class UCharacterWidget> widgetClass,
		FVector2D drawSize,
		EWidgetSpace newWidgetSpace = EWidgetSpace::Screen);

	void SetWidgetHeight(float widgetHeight);

};
