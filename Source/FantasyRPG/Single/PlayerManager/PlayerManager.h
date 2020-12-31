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
    // �÷��̾� ����
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
