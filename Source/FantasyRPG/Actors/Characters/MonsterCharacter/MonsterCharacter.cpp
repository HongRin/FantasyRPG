#include "MonsterCharacter.h"

#include "Actors/Controllers/MonsterController/MonsterController.h"
#include "Actors/InteractableActor/DropItem/DropItem.h"


#include "Components/PlayerDetector/PlayerDetectorComponent.h"
#include "Components/MonsterAttack/MonsterAttackComponent.h"
#include "Components/CharacterWidget/MonsterWidget/MonsterWidgetComponent.h"

#include "Enums/MonsterType.h"

#include "BrainComponent.h"

#include "Widgets/HpableCharacterWidget/HpableCharacterWidget.h"

#include "AnimInstances/MonsterCharacter/MonsterAnimInstance.h"

#include "Structures/Monster/MonsterInfo.h"
#include "Structures/ItemInfo/ItemInfo.h"

#include "Single/GameInstance/FRGameInstance.h"


AMonsterCharacter::AMonsterCharacter()
{
	// DT_EnemyData Asset Load
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MONSTER_DATA(
		TEXT("DataTable'/Game/Resources/DataTables/DT_MonsterInfo.DT_MonsterInfo'"));
	if (DT_MONSTER_DATA.Succeeded()) MonsterDatatable = DT_MONSTER_DATA.Object;
	else { UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: DT_MONSTER_DATA is not loaded!"), __LINE__); }
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ITEM_INFO(
		TEXT("DataTable'/Game/Resources/DataTables/DT_ItemInfo.DT_ItemInfo'"));
	if (DT_ITEM_INFO.Succeeded()) DTItemInfo = DT_ITEM_INFO.Object;
	else { UE_LOG(LogTemp, Error, TEXT("PlayerInventoryComponent.cpp :: %d LINE :: DT_ITEM_INFO is not loaded!"), __LINE__); }

	SetGenericTeamId(TEAM_MONSTER);

	// Component Initialization
	InitializeComponent();

	SetDropItems();
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	GameInst = Cast<UFRGameInstance>(GetGameInstance());

	// Set up the Monster Info
	InitializeMonsterDataConstructTime();

	// Set up the Widgets
	MonsterWidget->GetEnemyWidgetInstance()->InitializeWidget(this);
	MonsterWidget->GetEnemyWidgetInstance()->SetNameText(GetMonsterInfo()->MonsterName);
	MonsterWidget->GetEnemyWidgetInstance()->SetLevelText(GetMonsterInfo()->Lv);
	MonsterWidget->GetEnemyWidgetInstance()->SetLineHp(MonsterHpLine);
	MonsterWidget->GetEnemyWidgetInstance()->UpdateHp();

	if (GetMonsterInfo()->MonsterType == EMonsterType::MT_BOSS)
	{
		Tags.Add(TEXT("BsMonster"));
	}
	else Tags.Add(TEXT("Monster"));

	SetDropItems();
}

void AMonsterCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	MonsterWidget->GetEnemyWidgetInstance()->UpdateHp();
}

void AMonsterCharacter::OnCharacterDie()
{
	Super::OnCharacterDie();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	FString reason;
	Cast<AMonsterController>(GetController())->GetBrainComponent()->StopLogic(reason);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle,
		[this]() { 
			if (!(DropItems.Num() == 0))
			{
				UE_LOG(LogTemp, Warning, TEXT("DropItemSpawn"));
				ADropItem::SpawnItem(this, DropItems, GetActorLocation(), GetActorRotation());
			}
			Destroy(); },
		3.0f,
		false);
}

void AMonsterCharacter::InitializeComponent()
{
	PlayerDetector = CreateDefaultSubobject<UPlayerDetectorComponent>(TEXT("PLAYER_DETECTOR"));
	PlayerDetector->SetupAttachment(GetRootComponent());

	MonsterAttack = CreateDefaultSubobject<UMonsterAttackComponent>(TEXT("MONSTER_ATTACK"));

	MonsterWidget = CreateDefaultSubobject<UMonsterWidgetComponent>(TEXT("Monster_WIDGET"));
	MonsterWidget->SetupAttachment(GetRootComponent());

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}

void AMonsterCharacter::InitializeSkeletalMeshComponent()
{
	// Monster SkeletalMesh synchronous load
	auto monsterMesh = Cast<USkeletalMesh>(
		GameInst->GetStreamableManager()->LoadSynchronous(MonsterInfo.SkeletalMeshPath));
	
	// Anim Blueprint Asset Load
	UBlueprint* monsterAnimInstClass = Cast<UBlueprint>(
		GameInst->GetStreamableManager()->LoadSynchronous(MonsterInfo.AnimInstanceClassPath));

	UBlueprint* monsterAIControllerInstClass = Cast<UBlueprint>(
		GameInst->GetStreamableManager()->LoadSynchronous(MonsterInfo.AIControllerClassPath));
	
	if (IsValid(monsterMesh))
	{
		// Apply the loaded SkeletalMesh
		GetMesh()->SetSkeletalMesh(monsterMesh);
	
		// Set up the Location & Rotation
		GetMesh()->SetRelativeLocationAndRotation(
			FVector(0.0f, 0.0f, -(GetCapsuleComponent()->GetScaledCapsuleHalfHeight())),
			FRotator(0.0f, -90.0f, 0.0f));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monstermesh is not loaded!"), __LINE__);
	
	if (IsValid(monsterAnimInstClass))
	{
		// Cast as the AnimInstanceClass
		TSubclassOf<UMonsterAnimInstance> bpAnimInstClass = 
			static_cast<TSubclassOf<UMonsterAnimInstance>>(monsterAnimInstClass->GeneratedClass);
	
		// Apply AnimInstanceClass
		GetMesh()->SetAnimClass(bpAnimInstClass);
	}

	if (IsValid(monsterAIControllerInstClass))
	{
		TSubclassOf<AController> bpAIControllerClass =
			static_cast<TSubclassOf<AMonsterController>>(monsterAIControllerInstClass->GeneratedClass);

		AIControllerClass = bpAIControllerClass;
	}
}

void AMonsterCharacter::SetDropItems()
{
	FString contextString;

	UE_LOG(LogTemp, Warning, TEXT("MonsterInfo.DropItemCode.Num()::%d"), MonsterInfo.DropItemCode.Num());

	for (int i = 0; i < MonsterInfo.DropItemCode.Num(); ++i)
	{
		FItemInfo* itemInfo = DTItemInfo->FindRow<FItemInfo>(
			MonsterInfo.DropItemCode[i], contextString
			);
		if (itemInfo->value2 >= FMath::RandRange(1.0f, 100.0f))
		{
			if (MonsterInfo.MonsterType == EMonsterType::MT_BOSS)
			{
				DropItems.Add(FItemSlotInfo(itemInfo->ItemCode, FMath::RandRange(1.0f, itemInfo->value3)));
			}
			else
				DropItems.Add(FItemSlotInfo(itemInfo->ItemCode, 1));
		}
	}
}

void AMonsterCharacter::InitializeMonsterDataConstructTime()
{
	// Saves the Infomation that matches MonsterCode 
	FString contextString;
	FMonsterInfo* monsterInfo = MonsterDatatable->FindRow<FMonsterInfo>(
		MonsterCode, contextString
		);
	
	// Check for information found
	if (monsterInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monsterInfo is not loaded!"), __LINE__);
		return;
	}
	
	// Saves the MonsterInfo
	MonsterInfo = (*monsterInfo);
	
	// Set up the Hp
	Hp = MaxHp = monsterInfo->MaxHp;

	MonsterAtk = monsterInfo->Atk;
	
	// Set up the MaxWalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MaxSpeed;                                              
	
	// SkeletalMesh Initialization
	InitializeSkeletalMeshComponent();

	// Set up the Widget Location
	MonsterWidget->SetWidgetHeight(
		GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 30.0f);
}

void AMonsterCharacter::MonsterDash(FVector direction, float power)
{
	GetCharacterMovement()->AddImpulse(direction * power, true);
}

bool AMonsterCharacter::IsMovable() const
{
	return !GetMonsterAttack()->IsMonsterAttacking()
		
		&& !bIsDie;
}
