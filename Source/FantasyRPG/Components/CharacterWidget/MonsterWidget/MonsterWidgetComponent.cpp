#include "MonsterWidgetComponent.h"

#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Widgets/HpableCharacterWidget/HpableCharacterWidget.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

UMonsterWidgetComponent::UMonsterWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


	static ConstructorHelpers::FClassFinder<UHpableCharacterWidget> WIDGET_BP_Monster(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/WidgetBP_Monster.WidgetBP_Monster_C'"));
	if (WIDGET_BP_Monster.Succeeded())
		MonsterCharacterWidgetClass = WIDGET_BP_Monster.Class;
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterWidgetComponent.cpp :: %d LINE :: WIDGET_BP_ENEMY is not loaded!"), __LINE__);
	}


	if (IsValid(MonsterCharacterWidgetClass))
	{
		SetWidgetClass(MonsterCharacterWidgetClass);
		SetDrawSize(FVector2D(100.0f, 60.0f));
	}

}

void UMonsterWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	MonsterCharacter = Cast<AMonsterCharacter>(GetOwner());

	SetWidgetSpace(EWidgetSpace::Screen);
}

UHpableCharacterWidget* UMonsterWidgetComponent::GetEnemyWidgetInstance()
{
	return MonsterWidgetInstance = IsValid(MonsterWidgetInstance) ?
		MonsterWidgetInstance :
		Cast<UHpableCharacterWidget>(GetUserWidgetObject());
}

