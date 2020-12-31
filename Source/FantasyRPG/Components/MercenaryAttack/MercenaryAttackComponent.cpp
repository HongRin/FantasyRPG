#include "MercenaryAttackComponent.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

UMercenaryAttackComponent::UMercenaryAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackState = MERCENARY_ATTACK_NONE;
}

void UMercenaryAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	MercenaryCharacter = Cast<AMercenaryCharacter>(GetOwner());

	PlayerCharacter = Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn());

	OnMercenaryAttackFinished.AddLambda([this]()->void {
		AttackState = MERCENARY_ATTACK_NONE;
		});
}

void UMercenaryAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMercenaryAttackComponent::PlayMercenaryAttackAnimation()
{
	if (AttackState != MERCENARY_ATTACK_NONE) return;
	if (!IsValid(MercenaryAttack)) return;

	if (OnMercenaryAttackStarted.IsBound())
		OnMercenaryAttackStarted.Broadcast();

	if (FMath::FRandRange(0, 100) < MercenaryCharacter->GetMercenaryInfo()->SkillPercentage)
	{
		AttackState = MERCENARY_ATTACK_SKILL;
		MercenaryCharacter->PlayAnimMontage(MercenaryAttack, 1.0f, TEXT("Skill"));
	}
	else
	{
		AttackState = MERCENARY_ATTACK_BASIC;
		MercenaryCharacter->PlayAnimMontage(MercenaryAttack, 1.0f, TEXT("Attack"));
	}
}

void UMercenaryAttackComponent::ActiveMercenaryAttackRange()
{
	float attackRange = 100.0f;

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(MercenaryCharacter);
	actorsToIgnore.Add(PlayerCharacter);

	TArray<FHitResult> outHits;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		MercenaryCharacter->GetActorLocation(),
		MercenaryCharacter->GetActorLocation() + (MercenaryCharacter->GetActorForwardVector() * attackRange),
		100.0f,
		TEXT("AttackRange"),
		true,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		outHits,
		true,
		FLinearColor::Red,
		FLinearColor::Red,
		2.0f
	);

	for (auto hit : outHits)
	{
		if (!hit.GetActor()->ActorHasTag(TEXT("Mercenary")))
		{
			hit.GetActor()->TakeDamage(
				MercenaryCharacter->GetMercenaryInfo()->Atk,
				FDamageEvent(),
				MercenaryCharacter->GetController(),
				MercenaryCharacter);
		}
	}
}

