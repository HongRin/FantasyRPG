#include "InteractableNpc.h"
#include "Engine/DataTable.h"

#include "Components/ClosableWndController/ClosableWndControllerComponent.h"

#include "Structures/ShopInfo/ShopInfo.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/ClosableWnd/ClosableDialogWnd/ClosableDialogWnd.h"
#include "Widgets/ClosableWnd/DraggableWnd/ShopWnd/ShopWnd.h"
#include "Components/CanvasPanelSlot.h"



AInteractableNpc::AInteractableNpc()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ST_SHOP_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_ShopInfoDataTable.DT_ShopInfoDataTable'"));
	if (ST_SHOP_INFO.Succeeded()) DT_ShopInfo = ST_SHOP_INFO.Object;
	else { UE_LOG(LogTemp, Error, TEXT("IInteractableNpc.cpp :: %d LINE :: ST_SHOP_INFO is not loaded!"), __LINE__); }

	static ConstructorHelpers::FClassFinder<UShopWnd> BP_SHOP_WND(
		TEXT("WidgetBlueprint'/Game/Resources/Blueprints/Widgets/ClosableWnd/DraggableWnd/ShopWnd/BP_ShopWnd.BP_ShopWnd_C'"));
	if (BP_SHOP_WND.Succeeded()) ShopWndClass = BP_SHOP_WND.Class;
	else { UE_LOG(LogTemp, Error, TEXT("IInteractableNpc.cpp :: %d LINE :: BP_SHOP_WND is not loaded!"), __LINE__); }


	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL_MESH_COMPONENT"));
	InteractCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("INTERACT_CAMERA"));

	Mesh->SetupAttachment(GetRootComponent());
	InteractCamera->SetupAttachment(GetRootComponent());
}

void AInteractableNpc::BeginPlay()
{
	Super::BeginPlay();

	GameInst = Cast<UFRGameInstance>(GetGameInstance());
	PlayerManager = GameInst->GetManagerClass<UPlayerManager>();
}

void AInteractableNpc::OpenDialogWidget()
{
	// Npc 대화창 애셋 파일명
	FString closableNpcDialogAssetName = TEXT("ClosableDialogWnd_");
	closableNpcDialogAssetName.Append(NpcCode.ToString());

	// Npc 대화창 애셋 경로
	FString closableNpcWndPath = TEXT("/Game/Resources/Blueprints/Widgets/ClosableWnd/ClosableDialogWnd/");
	closableNpcWndPath.Append(closableNpcDialogAssetName);
	closableNpcWndPath.Append(TEXT("."));
	closableNpcWndPath.Append(closableNpcDialogAssetName);

	// 위젯 블루프린트 애셋 로드
	UBlueprint* closableDialogWndAsset = Cast<UBlueprint>(
		GameInst->GetStreamableManager()->LoadSynchronous(
			FSoftObjectPath(closableNpcWndPath)));

	
	if (IsValid(closableDialogWndAsset))
	{
		TSubclassOf<UClosableDialogWnd> bpClosableDialog =
			static_cast<TSubclassOf<UClosableDialogWnd>>(closableDialogWndAsset->GeneratedClass);
		
		UClosableDialogWnd* dialogWnd =
			PlayerManager->GetPlayerController()->GetClosableWndControllerComponent()->
			AddWnd<UClosableDialogWnd>(bpClosableDialog);
		
		dialogWnd->SetOwnerNpc(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InteractableNpc.cpp :: %d LINE :: closableDialogWndAsset is not loaded!"), __LINE__);
	}
	
}

void AInteractableNpc::Interaction()
{
	OpenDialogWidget();
}

UClosableWnd* AInteractableNpc::OpenShop(class UClosableWnd* parentWnd, FName shopID)
{
	FString contextString;
	FShopInfo* shopInfo = DT_ShopInfo->FindRow<FShopInfo>(shopID, contextString);

	UShopWnd* shopWnd = Cast<UShopWnd>(parentWnd->CreateChildClosableWnd(ShopWndClass));

	shopWnd->InitializeSaleList(shopInfo->SaleItems);

	return shopWnd;
}
