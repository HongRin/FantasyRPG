#pragma once

#include "Actors/InteractableActor/InteractableActor.h"
#include "Enums/ShopType.h"
#include "InteractableNpc.generated.h"

UCLASS()
class FANTASYRPG_API AInteractableNpc : public AInteractableActor
{
	GENERATED_BODY()
	
private:
	class UDataTable* DT_ShopInfo;
	TSubclassOf<class UShopWnd> ShopWndClass;
	TSubclassOf<class UMercenaryShopWnd> MercenaryShopWndClass;

	class UDataTable* DT_NPCDialogInfo;

private:
	UPROPERTY()
		class UFRGameInstance* GameInst;

	UPROPERTY()
		class UPlayerManager* PlayerManager;



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName NpcCode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FText NpcName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Type")
		EShopType ShopType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* InteractCamera;



public:
	AInteractableNpc();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OpenDialogWidget();

public:
	virtual void Interaction() override;

	class UClosableWnd* OpenShop(class UClosableWnd* parentWnd, FName shopID);
};
