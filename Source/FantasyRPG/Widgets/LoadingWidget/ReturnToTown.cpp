#include "ReturnToTown.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/TextBlock.h"
#include "Single/GameInstance/FRGameInstance.h"

void UReturnToTown::NativeConstruct()
{
	Super::NativeConstruct();

	Time = 5;

	Text_Loading = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Loading")));

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle,
		[this]() {
			--Time;
			if (Time == 0)
			{
				Cast<UFRGameInstance>(GetGameInstance())->SetNextLevelName(FName(TEXT("GameMap")));
				UGameplayStatics::OpenLevel(this, FName(TEXT("LoadingLevel")));
			}
			Text_Loading->SetText(FText::FromString(FString::FromInt(Time) + FString(TEXT("초 후 마을로 이동합니다."))));
		},
		1.0f,
			true);
}
