#pragma once

#include "FantasyRPG.h"
#include "GameFramework/Actor.h"
#include "DungeonPortal.generated.h"

UCLASS()
class FANTASYRPG_API ADungeonPortal : public AActor
{
	GENERATED_BODY()
	
private :
	TSubclassOf<class UDungeonChoiceWnd> BP_DungeonChoiceWnd;

private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName DCWCode;

public:	
	ADungeonPortal();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	UFUNCTION()
		void OnPortalOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
