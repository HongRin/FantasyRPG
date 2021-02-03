#include "MercenaryStateComponent.h"

#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"

#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Structures/MercenaryBlueprint/MercenaryBlueprint.h"


UMercenaryStateComponent::UMercenaryStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryInfo.DT_MercenaryInfo'"));
	if (DT_MERCENARY_INFO.Succeeded()) DT_MercenaryInfo = DT_MERCENARY_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryStateComponent.cpp::%d::LINE:: DT_MERCENARY_INFO is not loaded!"), __LINE__);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_BP(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryBlueprint.DT_MercenaryBlueprint'"));
	if (DT_MERCENARY_BP.Succeeded()) DT_MercenaryBP = DT_MERCENARY_BP.Object;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryStateComponent.cpp::%d::LINE:: DT_MERCENARY_BP is not loaded!"), __LINE__);
}


void UMercenaryStateComponent::BeginPlay()
{
	Super::BeginPlay();

	GameInst = Cast<UFRGameInstance>(GetWorld()->GetGameInstance());

}


void UMercenaryStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMercenaryStateComponent::InitializeScoutMercenarys()
{

}

void UMercenaryStateComponent::ScoutMercenary(FName mercenaryCode)
{
	FString contextString;
	FMercenaryInfo* mercenaryInfo = DT_MercenaryInfo->FindRow<FMercenaryInfo>(
		mercenaryCode, contextString);

	FMercenaryBlueprint* mercenaryblueprint = DT_MercenaryBP->FindRow<FMercenaryBlueprint>(
		mercenaryCode, contextString);

	ScoutMercenarys.Add(FMercenarySlotInfo(mercenaryCode));

	UBlueprint* mercenaryBPClass = Cast<UBlueprint>(
		GameInst->GetStreamableManager()->LoadSynchronous(mercenaryblueprint->BlueprintPath));

	if (IsValid(mercenaryBPClass))
	{
		// Cast as the AnimInstanceClass
		TSubclassOf<AMercenaryCharacter> bpInstClass =
			static_cast<TSubclassOf<AMercenaryCharacter>>(mercenaryBPClass->GeneratedClass);
	
		auto capsuleComponent = Cast<ACharacter>(GetOwner())->GetCapsuleComponent();

		AMercenaryCharacter* mercenaryCharacter =
			GetWorld()->SpawnActor<AMercenaryCharacter>(
			bpInstClass, 
				GetOwner()->GetActorLocation() + (FVector::UpVector * (capsuleComponent->GetScaledCapsuleHalfHeight() * 6.0f)),
				FRotator::ZeroRotator);

		UE_LOG(LogTemp, Warning, TEXT("IsValid(mercenaryCharacter) :: %d"), IsValid(mercenaryCharacter));

		MercenaryActors.Add(mercenaryCharacter);
	}
}
