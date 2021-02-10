#pragma once

#include "FantasyRPG.h"
#include "Structures/Player/PlayerInfo.h"
#include "Actors/Characters/MercenaryCharacter/MercenaryCharacter.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"
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

    TArray<FItemSlotInfo> InventoryItems;

    TArray<FMercenaryInfo> ParticipateInfo;
    
public:
    virtual void InitManagerClass() override;

public:
    FORCEINLINE FPlayerInfo* GetPlayerInfo()
    { return &PlayerInfo; }

    class ARPGPlayerController* GetPlayerController();

    FORCEINLINE void SetPlayerInventoryItems(TArray<FItemSlotInfo> inventoryItems)
    {
        InventoryItems = inventoryItems;
    }

    FORCEINLINE TArray<FItemSlotInfo>& GetInventoryItems()
    {
        return InventoryItems;
    }

    FORCEINLINE void SetParticipateInfo(TArray<FMercenaryInfo> participateInfo)
    {
        ParticipateInfo = participateInfo;
    }

    FORCEINLINE TArray<FMercenaryInfo>& GetParticipateInfo()
    {
        return ParticipateInfo;
    }
};
