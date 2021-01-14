#include "HealingParticleActor.h"

#include "Components/HealerSkillArea/HealerSkillAreaComponent.h"
#include "Components/HealerBehavior/HealerBehaviorComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Single/PlayerManager/PlayerManager.h"


AHealingParticleActor::AHealingParticleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HEALING(
		TEXT("ParticleSystem'/Game/VFX_Toolkit_V1/ParticleSystems/356Days/Par_HealLeaf_01.Par_HealLeaf_01'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_BUFF(
		TEXT("ParticleSystem'/Game/VFX_Toolkit_V1/ParticleSystems/356Days/Par_CloverField_01.Par_CloverField_01'"));

	if (P_HEALING.Succeeded()) HealingParticle = P_HEALING.Object;
	else UE_LOG(LogTemp, Error, TEXT("AHealingParticleActor.cpp::%d::LINE:: P_HEALING is not loaded!"), __LINE__);
	if (P_BUFF.Succeeded()) BuffParticle = P_BUFF.Object;
	else UE_LOG(LogTemp, Error, TEXT("AHealingParticleActor.cpp::%d::LINE:: P_BUFF is not loaded!"), __LINE__);

	SkillParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE_SYSTEM_COMP"));
	SetRootComponent(SkillParticleSystem);

	SkillArea = CreateDefaultSubobject<UHealerSkillAreaComponent>(TEXT("SKILL_AREA_COMP"));

	SetID(DEFAULT_SKILL);
}

void AHealingParticleActor::BeginPlay()
{
	Super::BeginPlay();
	
	SkillArea->SetHiddenInGame(false);

	SkillParticleSystem->OnSystemFinished.AddDynamic(
		this, &AHealingParticleActor::OnParticleSystemFinished);
}

void AHealingParticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHealingParticleActor::OnRecycleStart()
{

}

void AHealingParticleActor::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	SetCanRecyclable(true);
}

void AHealingParticleActor::PlayParticle(FVector loc, FRotator rot)
{
	SetActorLocationAndRotation(loc, rot);

	SkillParticleSystem->Activate(true);
	SkillParticleSystem->SetWorldLocationAndRotation(loc, rot);
	SkillArea->SetWorldLocationAndRotation(loc, rot);

	if (SkillState == SKILL_BUFF)
	{
		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			timerHandle,
			[this]() {
				SetCanRecyclable(true);
				SkillParticleSystem->Activate(false); },
			10.0f,
			false);
	}
}

void AHealingParticleActor::UpdateSkillSet(bool bIsHealing)
{
	if (bIsHealing)
	{
		SkillParticleSystem->SetTemplate(HealingParticle);
		SkillArea->SetSphereRadius(500.0f);
		SkillState = SKILL_HEALING;
	}
	else
	{
		SkillParticleSystem->SetTemplate(BuffParticle);
		SkillArea->SetSphereRadius(1000.0f);
		SkillState = SKILL_BUFF;
	}
}
