#include "MonsterAttackComponent.h"

#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"

UMonsterAttackComponent::UMonsterAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	AttackState = MONSTER_ATTACK_NONE;

	SkillPercentage = 30.0f;
}


void UMonsterAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	MonsterCharacter = Cast<AMonsterCharacter>(GetOwner());

	OnMonsterAttackFinished.AddLambda([this]()->void {
		AttackState = MONSTER_ATTACK_NONE;
	});
}


void UMonsterAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMonsterAttackComponent::PlayMonsterAttackAnimation()
{
	if (AttackState != MONSTER_ATTACK_NONE) return;
	if (!IsValid(MonsterAttack)) return;

	if (OnMonsterAttackStarted.IsBound())
		OnMonsterAttackStarted.Broadcast();

	if (FMath::FRandRange(0, 100) < SkillPercentage)
	{
		AttackState = MONSTER_ATTACK_SKILL;
		MonsterCharacter->PlayAnimMontage(MonsterAttack, 1.0f, TEXT("Skill"));
	}
	else
	{
		AttackState = MONSTER_ATTACK_BASIC;
		MonsterCharacter->PlayAnimMontage(MonsterAttack, 1.0f, TEXT("Attack"));
	}
}

void UMonsterAttackComponent::ActiveMonsterAttackRange()
{
	float attackRange = 100.0f;

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(MonsterCharacter);

	TArray<FHitResult> outHits;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		MonsterCharacter->GetActorLocation(),
		MonsterCharacter->GetActorLocation() + (MonsterCharacter->GetActorForwardVector() * attackRange),
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
		if (!hit.GetActor()->ActorHasTag(TEXT("Monster")))
		{
			hit.GetActor()->TakeDamage(
				MonsterCharacter->GetMonsterInfo()->Atk,
				FDamageEvent(),
				MonsterCharacter->GetController(),
				MonsterCharacter);
		}
	}
}

