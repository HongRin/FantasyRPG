#pragma once

#include "FantasyRPG.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ObjectPoolable.h"
#include "HealingParticleActor.generated.h"

#ifndef SKILL_STATE
#define SKILL_STATE

#define SKILL_HEALING 0
#define SKILL_BUFF 1
#endif

UCLASS()
class FANTASYRPG_API AHealingParticleActor : public AActor,
	public IObjectPoolable
{
	GENERATED_BODY()

private:
	class UParticleSystem* HealingParticle;
	class UParticleSystem* BuffParticle;

	class AMercenaryCharacter* HealerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* SkillParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UHealerSkillAreaComponent* SkillArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Id;

	UPROPERTY()
	bool bCanRecyclable;

	int32 SkillState;


public:
	AHealingParticleActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE virtual int32 GetID() const override
	{
		return Id;
	}

	FORCEINLINE virtual void SetID(int32 id)
	{
		Id = id;
	}

	// ���� ���� ���θ� ��Ÿ���� ������ ���� ������ / ������
	FORCEINLINE virtual bool GetCanRecyclable() const override
	{
		return bCanRecyclable;
	}

	FORCEINLINE virtual void SetCanRecyclable(bool canRecyclable) override
	{
		bCanRecyclable = canRecyclable;
	}

	// ��Ȱ���� �Ǵ� �������� ȣ��Ǵ� �޼���
	virtual void OnRecycleStart() override;

private:
	UFUNCTION()
		void OnParticleSystemFinished(class UParticleSystemComponent* PSystem);

public:
	void PlayParticle(FVector loc, FRotator rot = FRotator::ZeroRotator);

	void UpdateSkillSet(bool bIsHealing);

	FORCEINLINE int32 GetSkillState() const
	{
		return SkillState;
	}
};
