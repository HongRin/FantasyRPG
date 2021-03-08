#include "InteractableNpc.h"
#include "Engine/DataTable.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"
#include "Components/CharacterWidget/CharacterWidgetComponent.h"

#include "Structures/ShopInfo/ShopInfo.h"
#include "Structures/NPCDialogInfo/NPCDialogInfo.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/ClosableDialogWnd/ClosableDialogWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/ShopWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/MercenaryShopWnd/MercenaryShopWnd.h"
#include "Components/CanvasPanelSlot.h"

AInteractableNpc::AInteractableNpc()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DIALOG_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_DialogInfo.DT_DialogInfo'"));
	if (DT_DIALOG_INFO.Succeeded()) DT_NPCDialogInfo = DT_DIALOG_INFO.Object;
	else { UE_LOG(LogTemp, Error, TEXT("AInteractableNpc.cpp :: %d LINE :: DT_DIALOG_INFO is not loaded!"), __LINE__); }

	static ConstructorHelpers::FObjectFinder<UDataTable> ST_SHOP_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_ShopInfo.DT_ShopInfo'"));
	if (ST_SHOP_INFO.Succeeded()) DT_ShopInfo = ST_SHOP_INFO.Object;
	else { UE_LOG(LogTemp, Error, TEXT("AInteractableNpc.cpp :: %d LINE :: ST_SHOP_INFO is not loaded!"), __LINE__); }

	static ConstructorHelpers::FClassFinder<UShopWnd> BP_SHOP_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/ShopWnd/BP_ShopWnd.BP_ShopWnd_C'"));
	if (BP_SHOP_WND.Succeeded()) ShopWndClass = BP_SHOP_WND.Class;
	else { UE_LOG(LogTemp, Error, TEXT("AInteractableNpc.cpp :: %d LINE :: BP_SHOP_WND is not loaded!"), __LINE__); }

	static ConstructorHelpers::FClassFinder<UMercenaryShopWnd> BP_MR_SHOP_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/MercenaryShopWnd/BP_MercenaryShopWnd.BP_MercenaryShopWnd_C'"));
	if (BP_MR_SHOP_WND.Succeeded()) MercenaryShopWndClass = BP_MR_SHOP_WND.Class;
	else { UE_LOG(LogTemp, Error, TEXT("AInteractableNpc.cpp :: %d LINE :: BP_MR_SHOP_WND is not loaded!"), __LINE__); }

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL_MESH_COMPONENT"));
	InteractCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("INTERACT_CAMERA"));

	Mesh->SetupAttachment(GetRootComponent());
	InteractCamera->SetupAttachment(GetRootComponent());
}

void AInteractableNpc::BeginPlay()
{
	Super::BeginPlay();

	GameInst = Cast<UFRGameInstance>(GetGameInstance());
	PlayerManager = GetManager(UPlayerManager);

	Cast<UCharacterWidget>(CharacterWidget->GetUserWidgetObject())->SetNameText(NpcName);
}

void AInteractableNpc::OpenDialogWidget()
{
	// Npc 대화창 애셋 파일명
	//FString closableNpcDialogAssetName = TEXT("ClosableDialogWnd_");
	//closableNpcDialogAssetName.Append(NpcCode.ToString());
	//
	//// Npc 대화창 애셋 경로
	//FString closableNpcWndPath = TEXT("/Game/Resources/Blueprints/Widgets/ClosableWnd/ClosableDialogWnd/");
	//closableNpcWndPath.Append(closableNpcDialogAssetName);
	//closableNpcWndPath.Append(TEXT("."));
	//closableNpcWndPath.Append(closableNpcDialogAssetName);

	FString contextString;

	FNPCDialogInfo* dialogInfo = DT_NPCDialogInfo->FindRow<FNPCDialogInfo>(NpcCode, contextString);

	UClosableDialogWnd* dialogWnd =
		PlayerManager->GetPlayerController()->GetClosableWndControllerComponent()->
		//AddWnd<UClosableDialogWnd>(bpClosableDialog);
		AddWnd<UClosableDialogWnd>(dialogInfo->DialogClass);

	dialogWnd->SetOwnerNpc(this);
	dialogWnd->UpdateText(dialogInfo->MonsterName, dialogInfo->NPCDialog);
	dialogWnd->UpdateWndSize(1920.0f, 1080.0f);

	/*
	// 위젯 블루프린트 애셋 로드
	UBlueprint* closableDialogWndAsset = Cast<UBlueprint>(
		GameInst->GetStreamableManager()->LoadSynchronous(dialogInfo->DialogClassPath));

	if (IsValid(closableDialogWndAsset))
	{
		TSubclassOf<UClosableDialogWnd> bpClosableDialog =
			static_cast<TSubclassOf<UClosableDialogWnd>>(closableDialogWndAsset->GeneratedClass);
		
		UClosableDialogWnd* dialogWnd =
			PlayerManager->GetPlayerController()->GetClosableWndControllerComponent()->
			//AddWnd<UClosableDialogWnd>(bpClosableDialog);
			AddWnd<UClosableDialogWnd>(dialogInfo->DialogClass);
		
		dialogWnd->SetOwnerNpc(this);
		dialogWnd->UpdateText(dialogInfo->MonsterName, dialogInfo->NPCDialog);
		dialogWnd->UpdateWndSize(1920.0f, 1080.0f);

		//PlayerManager->GetPlayerController()->GetPlayerCharacterWidgetInstance()->SetLog(FText::FromString(TEXT("Add DialogWnd !")));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractableNpc.cpp :: %d LINE :: closableDialogWndAsset is not loaded!"), __LINE__);

		//PlayerManager->GetPlayerController()->GetPlayerCharacterWidgetInstance()->SetLog(FText::FromString(TEXT("closableDialogWndAsset is not loaded!")));
	}
	*/
}

void AInteractableNpc::Interaction()
{
	OpenDialogWidget();
}

UClosableWnd* AInteractableNpc::OpenShop(class UClosableWnd* parentWnd, FName shopID)
{
	FString contextString;
	FShopInfo* shopInfo = DT_ShopInfo->FindRow<FShopInfo>(shopID, contextString);

	if (ShopType == EShopType::ST_ITEM)
	{
		UShopWnd* shopWnd = Cast<UShopWnd>(parentWnd->CreateChildClosableWnd(ShopWndClass));

		shopWnd->InitializeSaleList(shopInfo->SaleItems);

		return shopWnd;
	}
	else if (ShopType == EShopType::ST_MERCENARY)
	{
		UMercenaryShopWnd* mercenaryShopWnd = Cast<UMercenaryShopWnd>(parentWnd->CreateChildClosableWnd(MercenaryShopWndClass));

		mercenaryShopWnd->InitializeMercenaryShopWnd(shopInfo->SaleItems);

		return mercenaryShopWnd;
	}
	else return nullptr;
}
