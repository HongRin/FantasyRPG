#pragma once

#include "FantasyRPG.h"
#include "Actors/InteractableActor/InteractableActor.h"
#include "Structures/ItemSlotInfo/ItemSlotInfo.h"
#include "DropItem.generated.h"

UCLASS()
class FANTASYRPG_API ADropItem : public AInteractableActor
{
	GENERATED_BODY()

private:
	TSubclassOf<class UItemDropWnd> ItemDropWndClass;

private :
	TArray<FItemSlotInfo> Items;

public :
	ADropItem();
	
protected :
	virtual void BeginPlay() override;

public :
	static ADropItem* SpawnItem(UObject* contextObj, TArray<FItemSlotInfo> items, FVector location, FRotator rotation = FRotator::ZeroRotator);

protected :
	virtual void Interaction() override;

public :
	FORCEINLINE void ItemEmpty(int32 index)
	{ Items[index] = FItemSlotInfo(); }
};
