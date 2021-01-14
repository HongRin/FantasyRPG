#include "PlayerAttackComponent.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Single/PlayerManager/PlayerManager.h"

UPlayerAttackComponent::UPlayerAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsLRegularAttack = false;

	LoadAsset();
}


void UPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	OnLComboAttackFinished.AddLambda([this]()->void {
		bIsLRegularAttack = bIsLFirstComboAttack = bIsLSecondComboAttack = false;
		});
	OnRComboAttackFinished.AddLambda([this]()->void {
		bIsRRegularAttack = bIsRFirstComboAttack = false;
		});
}


void UPlayerAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerAttackComponent::LoadAsset()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ATTACK(
		TEXT("AnimMontage'/Game/Resources/Characters/PlayerCharacters/StylizedSwordman/Characters/Animations/Female/AM_ATTACK.AM_ATTACK'"));
	if (AM_ATTACK.Succeeded()) RegularAttackAnimMotage = AM_ATTACK.Object;
	else
	{
		UE_LOG(LogTemp, Error, TEXT("RegularAttackAnimMotage is not Load!"));
	}
}

void UPlayerAttackComponent::LRegularAttack()
{
	if (PlayerCharacter->IsInAir()) return;

	if (OnRComboAttackFinished.IsBound())
		OnRComboAttackFinished.Broadcast();
	if (bIsLFirstComboAttack)
		bIsLSecondComboAttack = true;
	else if (bIsLRegularAttack)
		bIsLFirstComboAttack = true;
	else
	{
		bIsLRegularAttack = true;
		PlayerCharacter->PlayAnimMontage(RegularAttackAnimMotage);
	}
}

void UPlayerAttackComponent::RRegularAttack()
{
	if (PlayerCharacter->IsInAir()) return;

	if (OnLComboAttackFinished.IsBound())
		OnLComboAttackFinished.Broadcast();

	if (bIsRRegularAttack)
		bIsRFirstComboAttack = true;
	else
	{
		bIsRRegularAttack = true;
		PlayerCharacter->PlayAnimMontage(RegularAttackAnimMotage, 1.0f, TEXT("RAttack1"));
	}
}

void UPlayerAttackComponent::UpdateAttackRange(float radius, float length)
{
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(PlayerCharacter);

	TArray<FHitResult> hitResults;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		PlayerCharacter->GetActorLocation(),
		PlayerCharacter->GetActorLocation() + (PlayerCharacter->GetActorForwardVector() * length),
		radius,
		TEXT("AttackRange"),
		true,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		hitResults,
		true);

	for (auto hit : hitResults)
	{

		hit.GetActor()->TakeDamage(
			PlayerCharacter->GetPlayerManager()->GetPlayerInfo()->Atk,
			FDamageEvent(),
			PlayerCharacter->GetController(),
			PlayerCharacter);
	}
}

