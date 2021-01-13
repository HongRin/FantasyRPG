#include "HealerSkillAreaComponent.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Actors/PoolableParticleActor/HealingParticleActor/HealingParticleActor.h"

#include "Components/PlayerWndController/PlayerWndControllerComponent.h"

#include "Structures/Player/PlayerInfo.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/FRGameInstance.h"

#include "Widgets/HpableCharacterWidget/PlayerCHaracterWidget/PlayerCharacterWidget.h"


UHealerSkillAreaComponent::UHealerSkillAreaComponent()
{
	SphereRadius = 200.0f;
}

void UHealerSkillAreaComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UHealerSkillAreaComponent::OnInSkillArea);
	OnComponentEndOverlap.AddDynamic(this, &UHealerSkillAreaComponent::OnOutSkillArea);

}

void UHealerSkillAreaComponent::OnInSkillArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn()))
	{
		if (OtherComp == Cast<APlayerCharacter>(OtherActor)->GetCapsuleComponent())
		{
			if (Cast<AHealingParticleActor>(GetOwner())->GetSkillState() == 0)
			{
				GetManager(UPlayerManager)->GetPlayerInfo()->Hp += 200;
				Cast<APlayerCharacter>(OtherActor)->GetPlayerController()->GetPlayerCharacterWidgetInstance()->UpdateHp();
			}
			else
			{
				GetManager(UPlayerManager)->GetPlayerInfo()->Atk += 20;
			}
		}
	}

	if (OtherActor->ActorHasTag(TEXT("Mercenary")))
	{
		if (OtherComp == Cast<AMercenaryCharacter>(OtherActor)->GetCapsuleComponent())
		{
			UE_LOG(LogTemp, Warning, TEXT("MercenaryHealing"));
		}
	}
}

void UHealerSkillAreaComponent::OnOutSkillArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Cast<APlayerCharacter>(GetManager(UPlayerManager)->GetPlayerController()->GetPawn()))
	{
		if (OtherComp == Cast<APlayerCharacter>(OtherActor)->GetCapsuleComponent())
		{
			if (Cast<AHealingParticleActor>(GetOwner())->GetSkillState() == 1)
			{
				GetManager(UPlayerManager)->GetPlayerInfo()->Atk -= 20;
			}
		}
	}

	if (OtherActor->ActorHasTag(TEXT("Mercenary")))
	{
		if (OtherComp == Cast<AMercenaryCharacter>(OtherActor)->GetCapsuleComponent())
		{
		}
	}
}

