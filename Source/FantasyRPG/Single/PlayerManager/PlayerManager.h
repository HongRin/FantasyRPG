#pragma once

#include "FantasyRPG.h"
#include "Structures/Player/PlayerInfo.h"
#include "Single/ManagerClass/ManagerClass.h"
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


public:
    virtual void InitManagerClass() override;

public:
    FORCEINLINE FPlayerInfo* GetPlayerInfo()
    { return &PlayerInfo; }

    class ARPGPlayerController* GetPlayerController();


};
