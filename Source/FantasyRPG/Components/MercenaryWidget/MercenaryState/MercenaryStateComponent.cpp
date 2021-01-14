#include "MercenaryStateComponent.h"

#include "Engine/DataTable.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


UMercenaryStateComponent::UMercenaryStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryInfo.DT_MercenaryInfo'"));
	if (DT_MERCENARY_INFO.Succeeded()) DT_MercenaryInfo = DT_MERCENARY_INFO.Object;
	else UE_LOG(LogTemp, Error, TEXT("UMercenaryStateComponent.cpp::%d::LINE:: DT_MERCENARY_INFO is not loaded!"), __LINE__);
}


void UMercenaryStateComponent::BeginPlay()
{
	Super::BeginPlay();

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

	ScoutMercenarys.Add(FMercenarySlotInfo(mercenaryCode));
}

