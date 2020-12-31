#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PlayerInteractionComponent.generated.h"

UCLASS()
class FANTASYRPG_API UPlayerInteractionComponent : public USphereComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
		class APlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<class AInteractableActor*> InteractableActors;

	UPROPERTY()
		bool bIsInteracting;

public:
	UPlayerInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float dt, ELevelTick tickType, FActorComponentTickFunction* thisTickFunc) override;

public:
	void TryInteraction();

private:
	void SortByDistance();

	UFUNCTION()
		void OnInteractableActorDetected(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnInteractableActorLose(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

};
