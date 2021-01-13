#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "HealerSkillAreaComponent.generated.h"

UCLASS()
class FANTASYRPG_API UHealerSkillAreaComponent : public USphereComponent
{
	GENERATED_BODY()

public :
	UHealerSkillAreaComponent();

private :
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnInSkillArea(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOutSkillArea (
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
};
