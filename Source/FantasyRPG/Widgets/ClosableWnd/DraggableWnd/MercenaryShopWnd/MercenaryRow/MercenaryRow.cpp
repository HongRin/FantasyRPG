#include "MercenaryRow.h"
#include "Engine/DataTable.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Structures/MercenaryInfo/MercenaryInfo.h"

UMercenaryRow::UMercenaryRow(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MERCENARY_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MercenaryInfo.DT_MercenaryInfo'"));
	if (DT_MERCENARY_INFO.Succeeded()) DT_MercenaryInfo = DT_MERCENARY_INFO.Object;
	else UE_LOG(LogTemp, Warning, TEXT("UMercenaryRow.cpp::%d::LINE::DT_MERCENARY_INFO is not loaded"), __LINE__);

}

void UMercenaryRow::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Name    = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Name"))); 
	Text_Costs   = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Costs")));
	Button_Scout = Cast<UButton>(GetWidgetFromName(TEXT("Button_Scout")));

	Button_Scout->OnClicked.AddDynamic(this, &UMercenaryRow::OnScoutButtonClicked);
}

void UMercenaryRow::UpdateMercenaryRow(FName mercenaryCode)
{
	FString contextSting;
	FMercenaryInfo* mercenaryInfo = DT_MercenaryInfo->FindRow<FMercenaryInfo>(
		mercenaryCode, contextSting);

	Text_Name->SetText(mercenaryInfo->MercenaryName);
	Text_Costs->SetText(FText::FromString(FString::FromInt(mercenaryInfo->Cost)));
}

void UMercenaryRow::OnScoutButtonClicked()
{
}
