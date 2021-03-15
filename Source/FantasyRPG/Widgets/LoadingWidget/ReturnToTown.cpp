#include "ReturnToTown.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/TextBlock.h"
#include "Single/GameInstance/FRGameInstance.h"

void UReturnToTown::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Loading = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Loading")));

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle,
		[this]() {
			--Time;
			if (Time == 0)
			{
				Cast<UFRGameInstance>(GetGameInstance())->SetNextLevelName(FName(TEXT("MapGame")));
				UGameplayStatics::OpenLevel(this, FName(TEXT("LoadingLevel")));
			}
		},
		1.0f,
			true);
}
