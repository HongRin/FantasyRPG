#include "DungeonPortal.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/DungeonChoiceWnd/DungeonChoiceWnd.h"
#include "Widgets/HpableCharacterWidget/PlayerCharacterWidget/PlayerCharacterWidget.h"

#include "Particles/ParticleSystemComponent.h"

ADungeonPortal::ADungeonPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UDungeonChoiceWnd> BP_DUNGEON_CHOICE_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/ClosableDungeonWnd/BP_DungeonChoiceWnd.BP_DungeonChoiceWnd_C'"));
	if (BP_DUNGEON_CHOICE_WND.Succeeded()) BP_DungeonChoiceWnd = BP_DUNGEON_CHOICE_WND.Class;
	else UE_LOG(LogTemp, Error, TEXT("ADungeonPortal.cpp::%d::LINE:: BP_DUNGEON_CHOICE_WND is not loaded"), __LINE__);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX_TRIGGER"));
	SetRootComponent(Box);
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE_SYSTEM_COMP"));
	ParticleSystem->SetupAttachment(GetRootComponent());

	Box->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ADungeonPortal::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ADungeonPortal::OnPortalOverlap);
	ParticleSystem->Activate(true);
	ParticleSystem->SetWorldLocationAndRotation(GetActorLocation(), GetActorRotation() + FRotator(0.0f, 0.0f, 180.0f));

}

void ADungeonPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADungeonPortal::OnPortalOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(GetManager(UPlayerManager)->
			GetPlayerController()->GetPawn());

		if (playerCharacter->GetCapsuleComponent() == OtherComp)
		{
			UDungeonChoiceWnd* dungeonChoiceWnd = GetManager(UPlayerManager)->GetPlayerController()->GetClosableWndControllerComponent()->AddWnd<UDungeonChoiceWnd>(BP_DungeonChoiceWnd);
			dungeonChoiceWnd->InitializeDCW(DCWCode);
			playerCharacter->ProhibitMove();

			playerCharacter->GetPlayerController()->SetInputMode(FInputModeUIOnly());
			playerCharacter->GetPlayerController()->bShowMouseCursor = true;
		}
	}
}