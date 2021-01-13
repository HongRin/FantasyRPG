#include "HealerBehaviorComponent.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actors/PoolableParticleActor/HealingParticleActor/HealingParticleActor.h"
#include "Util/ObjectPool.h"


UHealerBehaviorComponent::UHealerBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AHealingParticleActor> BP_HEAL(
		TEXT("Blueprint'/Game/Resources/Blueprints/Actors/Particles/P_Healing.P_Healing_C'"));
	if (BP_HEAL.Succeeded()) HealParticle = BP_HEAL.Class;

	SkillState = HEALER_SKILL_NONE;
}


void UHealerBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	ParticleObjectPool = NewObject<UObjectPool>();

	HealerCharacter = Cast<AMercenaryCharacter>(GetOwner());

	PlayerCharacter = Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn());

	OnHealerSkillFinished.AddLambda([this]()->void {
		SkillState = HEALER_SKILL_NONE;
		});
}


void UHealerBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

AHealingParticleActor* UHealerBehaviorComponent::PlaySkillParticle(FVector loc, FRotator rot)
{
	auto skillParticle = Cast<AHealingParticleActor>(
		ParticleObjectPool->GetRecycledObjectById(DEFAULT_SKILL));

	if (!IsValid(skillParticle))
	{
		ParticleObjectPool->RegisterRecyclableObject(
			skillParticle = GetWorld()->SpawnActor<AHealingParticleActor>(HealParticle));
	}

	if (SkillState == HEALER_SKILL_HEALING)
	skillParticle->UpdateSkillSet(true);
	else skillParticle->UpdateSkillSet(false);

	skillParticle->PlayParticle(loc, rot);

	return skillParticle;
}

void UHealerBehaviorComponent::PlayHealingAnimation()
{
	if (SkillState != HEALER_SKILL_NONE) return;
	if (!IsValid(AM_Healing_Asset)) return;
	
	if (HealerCharacter->GetMercenaryInfo()->SkillPercentage >= FMath::RandRange(1.0f, 100.0f))
	{
		SkillState = HEALER_SKILL_HEALING;
		UE_LOG(LogTemp, Warning, TEXT("PlayHealingAnimation"));
		HealerCharacter->PlayAnimMontage(AM_Healing_Asset, 1.0f, TEXT("Healing"));
		PlaySkillParticle(HealerCharacter->GetActorLocation());
	}
	else
	{
		SkillState = HEALER_SKILL_BUFF;
		UE_LOG(LogTemp, Warning, TEXT("PlayBuffAnimation"));
		HealerCharacter->PlayAnimMontage(AM_Healing_Asset, 1.0f, TEXT("Buff"));
		PlaySkillParticle(HealerCharacter->GetActorLocation());
	}
}

