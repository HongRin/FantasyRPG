#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealerBehaviorComponent.generated.h"

#ifndef HEALER_SKILL_TYPE
#define HEALER_SKILL_TYPE

#define HEALER_SKILL_NONE -1
#define HEALER_SKILL_HEALING 0
#define HEALER_SKILL_BUFF 1
#endif

#ifndef SKILL_PARTICLE_ID
#define SKILL_PARTICLE_ID

#define DEFAULT_SKILL			1

#endif

DECLARE_MULTICAST_DELEGATE(FOnHealerSkillEventSignature)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASYRPG_API UHealerBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public :
	FOnHealerSkillEventSignature OnHealerSkillFinished;

public:	
	UHealerBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	UPROPERTY()
		TSubclassOf<class AHealingParticleActor> HealParticle;

	UPROPERTY()
	class AMercenaryCharacter* HealerCharacter;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* AM_Healing_Asset;

	UPROPERTY()
	int32 SkillState;

	// 파티클 액터 풀
	UPROPERTY()
		class UObjectPool* ParticleObjectPool;

private :
	class AHealingParticleActor* PlaySkillParticle(FVector loc, FRotator rot = FRotator::ZeroRotator);

public:
	void PlayHealingAnimation();

	FORCEINLINE bool IsHealerSkillNone() const
	{
		return SkillState != HEALER_SKILL_NONE;
	};
};
