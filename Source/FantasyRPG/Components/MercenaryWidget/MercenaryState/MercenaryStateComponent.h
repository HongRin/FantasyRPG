#pragma once

#include "FantasyRPG.h"
#include "Components/ActorComponent.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "Structures/MercenarySlotInfo/MercenarySlotInfo.h"
#include "MercenaryStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASYRPG_API UMercenaryStateComponent : public UActorComponent
{
	GENERATED_BODY()
private :
	// 고용하고 있는 용병들을 나타냅니다.
	TArray<FMercenarySlotInfo> ScoutMercenarys;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<class AMercenaryCharacter*> MercenaryActors;

	class UDataTable* DT_MercenaryInfo;

	class UDataTable* DT_MercenaryBP;

	class UFRGameInstance* GameInst;

public:	
	UMercenaryStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 용병을 초기화합니다.
	void InitializeScoutMercenarys();

public :
	void ScoutMercenary(FName mercenaryCode);

public :
	FORCEINLINE const TArray<FMercenarySlotInfo>& GetScoutMercenarys() const
	{
		return ScoutMercenarys;
	}

	//FMercenaryInfo* GetScoutMercenaryInfo(int32 index);
};
