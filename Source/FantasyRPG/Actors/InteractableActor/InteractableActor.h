#pragma once

#include "FantasyRPG.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInteractionFinishedSignature)

UCLASS(Abstract)
class FANTASYRPG_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	class UCharacterWidgetComponent* CharacterWidget;

	FOnInteractionFinishedSignature OnInteractionFinished;

public:	
	AInteractableActor();

protected:
	virtual void BeginPlay() override;

public:
	void StartInteraction(FOnInteractionFinishedSignature interactionFinishedEvent);

	UFUNCTION()
		void FinishInteraction();

protected:
	virtual void Interaction() PURE_VIRTUAL(AInteractableActor::Interaction, );


};
