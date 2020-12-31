#include "InteractableActor.h"
#include "Components/ArrowComponent.h"
#include "Components/CharacterWidget/CharacterWidgetComponent.h"
#include "Widgets/CharacterWidget.h"

AInteractableActor::AInteractableActor()
{
	static ConstructorHelpers::FClassFinder<UCharacterWidget> WIDGET_BP_CHARACTER(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/WidgetBP_Character.WidgetBP_Character_C'"));



	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE_COMPONENT"));
	CharacterWidget = CreateDefaultSubobject<UCharacterWidgetComponent>(TEXT("INTERACTABLE_ACTOR_WIDGET"));
	SetRootComponent(Capsule);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW_COMPONENT"));
	Arrow->SetupAttachment(GetRootComponent());
	CharacterWidget->SetupAttachment(GetRootComponent());

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);

	if (WIDGET_BP_CHARACTER.Succeeded())
		CharacterWidget->InitializeCharaterWidget(WIDGET_BP_CHARACTER.Class, FVector2D(100.0f, 30.0f));

}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	CharacterWidget->SetWidgetHeight(Capsule->GetScaledCapsuleHalfHeight() + 10.0f);
}

void AInteractableActor::StartInteraction(FOnInteractionFinishedSignature interactionFinishedEvent)
{
	Interaction();
	
	OnInteractionFinished = interactionFinishedEvent;
}

void AInteractableActor::FinishInteraction()
{
	if (OnInteractionFinished.IsBound())
	{
		OnInteractionFinished.Broadcast();

		OnInteractionFinished.Clear();
	}
}

