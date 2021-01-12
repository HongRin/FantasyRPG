#include "DropItem.h"

#include "Engine/Engine.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/FRGameInstance.h"

#include "Widgets/CharacterWidget.h"
#include "Widgets/ClosableWnd/DraggableWnd/DropItemWnd/ItemDropWnd.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"
#include "Components/CharacterWidget/CharacterWidgetComponent.h"


#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADropItem::ADropItem()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UItemDropWnd> BP_ITEM_DROP_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/ItemDropWnd/BP_ItemDropWnd.BP_ItemDropWnd_C'"));
	if (BP_ITEM_DROP_WND.Succeeded()) ItemDropWndClass = BP_ITEM_DROP_WND.Class;
	else UE_LOG(LogTemp, Warning, TEXT("ADropItem.cpp::%d::LINE:: BP_ITEM_DROP_WND is not loaded! "), __LINE__);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_DROP_ITEM_EFFECT(
		TEXT("ParticleSystem'/Game/Resources/Particles/InfinityBladeEffects/Effects/FX_Ability/Summon/P_Summon_Portal.P_Summon_Portal'"));
	if (PS_DROP_ITEM_EFFECT.Succeeded()) Particle = PS_DROP_ITEM_EFFECT.Object;

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE_SYSTEM_COMP"));

	CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CHARACTER_MOVEMENT"));

	CharacterMovement->GravityScale = 1.0f;

	ParticleSystem->SetTemplate(Particle);
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();

	Capsule->SetCapsuleRadius(50.0f);
	Capsule->SetCapsuleHalfHeight(50.0f);

	Capsule->SetHiddenInGame(false);

	Capsule->SetSimulatePhysics(true);

	Capsule->SetCollisionProfileName(TEXT("DropItemCollision"));

	Cast<UCharacterWidget>(CharacterWidget->GetUserWidgetObject())->SetNameText(FText::FromString(TEXT(" ")));
}

void ADropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ParticleSystem->SetWorldLocationAndRotation(GetActorLocation() - FVector(0.0f, 0.0f, 120.0f), FRotator::ZeroRotator);
}

ADropItem* ADropItem::SpawnItem(UObject* contextObj, TArray<FItemSlotInfo> items, FVector location, FRotator rotation)
{
	ADropItem* newWorldItem = GEngine->GetWorldFromContextObject(contextObj)->
		SpawnActor<ADropItem>(ADropItem::StaticClass(), location, rotation);
	 
	newWorldItem->Items = items;

	newWorldItem->PlayPartice();

	return newWorldItem;
}

void ADropItem::Interaction()
{
	auto itemRootWnd = GetManager(UPlayerManager)->GetPlayerController()->
		GetClosableWndControllerComponent()->AddWnd<UItemDropWnd>(ItemDropWndClass);

	itemRootWnd->InitializeRootItems(Items);
	itemRootWnd->SetDropItem(this);
	itemRootWnd->onWndClosed.AddLambda([this]() { FinishInteraction(); });
}

void ADropItem::PlayPartice()
{
	ParticleSystem->Activate(true);
}
