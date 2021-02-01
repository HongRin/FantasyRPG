#include "PlayerInteractionComponent.h"

#include "Actors/InteractableActor/InteractableActor.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Components/ClosableWndController/ClosableWndControllerComponent.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SphereRadius = 500.0f;
}

void UPlayerInteractionComponent::BeginPlay()
{
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	OnComponentBeginOverlap.AddDynamic(this, &UPlayerInteractionComponent::OnInteractableActorDetected);
	OnComponentEndOverlap.AddDynamic(this, &UPlayerInteractionComponent::OnInteractableActorLose);
}

void UPlayerInteractionComponent::TickComponent(float dt, ELevelTick tickType, FActorComponentTickFunction* thisTickFunc)
{
	Super::TickComponent(dt, tickType, thisTickFunc);

	SortByDistance();
}

void UPlayerInteractionComponent::TryInteraction()
{
	if (bIsInteracting) return;

	if (InteractableActors.Num() == 0) return;

	FOnInteractionFinishedSignature interactionFinEvent;
	interactionFinEvent.AddLambda([this]() -> void
		{
			PlayerCharacter->AllowMove();

			PlayerCharacter->GetPlayerController()->ChangeViewTarget(nullptr);

			bIsInteracting = false;
		});

	PlayerCharacter->ProhibitMove();

	PlayerCharacter->GetPlayerController()->SetInputMode(FInputModeUIOnly());
	PlayerCharacter->GetPlayerController()->bShowMouseCursor = true;


	InteractableActors[0]->StartInteraction(interactionFinEvent);
	bIsInteracting = true;

	PlayerCharacter->GetPlayerController()->ChangeViewTarget(InteractableActors[0]);
}

void UPlayerInteractionComponent::SortByDistance()
{
	for (int i = 0; i < InteractableActors.Num(); ++i)
	{
		for (int j = 0; j < InteractableActors.Num() - (i + 1); ++i)
		{
			float current = FVector::Distance(
				InteractableActors[j]->GetActorLocation(),
				GetComponentLocation());

			float next = FVector::Distance(
				InteractableActors[j + 1]->GetActorLocation(),
				GetComponentLocation());

			if (current > next)
			{
				auto temp = InteractableActors[j];
				InteractableActors[j] = InteractableActors[j + 1];
				InteractableActors[j + 1] = temp;
			}
		}
	}
}

void UPlayerInteractionComponent::OnInteractableActorDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AInteractableActor* interactableActor = Cast<AInteractableActor>(OtherActor);

	if (!IsValid(interactableActor)) return;

	if (InteractableActors.Contains(interactableActor)) return;

	InteractableActors.Add(interactableActor);
}

void UPlayerInteractionComponent::OnInteractableActorLose(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AInteractableActor* interactableActor = Cast<AInteractableActor>(OtherActor);

	if (!IsValid(interactableActor)) return;

	if (!InteractableActors.Contains(interactableActor)) return;

	InteractableActors.Remove(interactableActor);
}
