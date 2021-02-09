#pragma once

#include "FantasyRPG.h"
#include "Structures/Player/PlayerInfo.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "PlayerManager.generated.h"

UCLASS()
class FANTASYRPG_API UPlayerManager : public UManagerClass 
{
    GENERATED_BODY()


private:
    // 플레이어 정보
    FPlayerInfo PlayerInfo;

    UPROPERTY()
    class ARPGPlayerController* PlayerController;

    UPROPERTY()
    TArray<AMercenaryCharacter> ParticipateMercenary;

public:
    virtual void InitManagerClass() override;

public:
    FORCEINLINE FPlayerInfo* GetPlayerInfo()
    { return &PlayerInfo; }

    class ARPGPlayerController* GetPlayerController();

    FORCEINLINE void SetParticipateMercenary(TArray<AMercenaryCharacter> participateMercenary)
    {
        ParticipateMercenary = participateMercenary;
    }

    FORCEINLINE const TArray<AMercenaryCharacter> GetParticipateMercenary() const
    {
        return ParticipateMercenary;
    }
};
