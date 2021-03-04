#include "PlayerCharacter.h"

#include "Actors/Controllers/PlayerController/RPGPlayerController.h"
#include "Actors/InteractableActor/DropItem/DropItem.h"

#include "Components/ZoomableSpringArm/ZoomableSpringArmComponent.h"
#include "Components/PlayerAttack/PlayerAttackComponent.h"
#include "Components/PlayerInteraction/PlayerInteractionComponent.h"
#include "Components/PlayerInventory/PlayerInventoryComponent.h"
#include "Components/PlayerWndController/PlayerWndControllerComponent.h"
#include "Components/MercenaryWidget/MercenaryState/MercenaryStateComponent.h"

#include "AnimInstances/PlayerCharacter/PlayerAnimInstance.h"

#include "Structures/Player/PlayerInfo.h"
#include "Structures/EquipItem/EquipItemInfo.h"

#include "Single/GameInstance/FRGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/HpableCharacterWidget/PlayerCHaracterWidget/PlayerCharacterWidget.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetGenericTeamId(TEAM_PLAYER);

	// 컨트롤러 Yaw 회전을 사용하지 않도록 설정
	bUseControllerRotationYaw = false;

	// 이동 방향으로 회전
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	JumpMaxCount = 2;

	DashDelay = 2;

	bIsMoveable = true;

	bIsDied = false;

	GetCharacterMovement()->JumpZVelocity = 500;

	LoadAsset();

	InitializeComponets();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetPlayerManager()->GetPlayerInfo()->Initialize();

	UpdateEquipItemState(true);

	Tags.Add(TEXT("Player"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -75.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void APlayerCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(
		DamagedActor,
		Damage,
		DamageType,
		InstigatedBy,
		DamageCauser);

	PlayerController->GetPlayerCharacterWidgetInstance()->UpdateHp();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Walk();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

#pragma region Action
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_DoubleClick,
		this, &APlayerCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released,
		this, &APlayerCharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Released,
		this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, PlayerInteraction, &UPlayerInteractionComponent::TryInteraction);

	PlayerInputComponent->BindAction(TEXT("LRegularAttack"), EInputEvent::IE_Released,
		PlayerAttack, &UPlayerAttackComponent::LRegularAttack);
	PlayerInputComponent->BindAction(TEXT("RRegularAttack"), EInputEvent::IE_Released,
		PlayerAttack, &UPlayerAttackComponent::RRegularAttack);
	PlayerInputComponent->BindAction(TEXT("Status"), EInputEvent::IE_Pressed, 
		PlayerWndController, &UPlayerWndControllerComponent::ToggleStatus);
	PlayerInputComponent->BindAction(TEXT("Inventory"), EInputEvent::IE_Pressed,
		PlayerWndController, &UPlayerWndControllerComponent::ToggleInventory);
	PlayerInputComponent->BindAction(TEXT("MercenaryWnd"), EInputEvent::IE_Pressed,
		PlayerWndController, &UPlayerWndControllerComponent::ToggleMercenaryWnd);


	PlayerInputComponent->BindAction(TEXT("SkillTest"), EInputEvent::IE_Pressed,
		this, &APlayerCharacter::SkillTest);
#pragma endregion

#pragma region Axis
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerCharacter::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerCharacter::InputVertical);
	PlayerInputComponent->BindAxis(TEXT("MouseWheel"), SpringArm,
		&UZoomableSpringArmComponent::ZoomCamera);
#pragma endregion
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<ARPGPlayerController>(NewController);
}

float APlayerCharacter::GetMaxHp()
{
	return GetPlayerManager()->GetPlayerInfo()->MaxHp;
}

float APlayerCharacter::GetHp()
{
	return GetPlayerManager()->GetPlayerInfo()->Hp;
}

void APlayerCharacter::SetHp(float value)
{
	GetPlayerManager()->GetPlayerInfo()->Hp = value;
}

void APlayerCharacter::OnCharacterDie()
{
	Super::OnCharacterDie();

	bIsMoveable = false;

	bIsDied = true;
}



void APlayerCharacter::LoadAsset()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SWORDMAN(TEXT("SkeletalMesh'/Game/Resources/Characters/PlayerCharacters/StylizedSwordman/Characters/Meshes/Female/SK_Female_SwordMan.SK_Female_SwordMan'"));
	if (SK_SWORDMAN.Succeeded()) BodyMeshAsset = SK_SWORDMAN.Object;
	else { UE_LOG(LogTemp, Error, TEXT("RPGCharacter.cpp :: %d LINE :: SK_BASE_BODY is not loaded!"), __LINE__); }
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SWORDMANHAIR(TEXT("SkeletalMesh'/Game/Resources/Characters/PlayerCharacters/Common/Hair/Mesh/Female/SK_FemaleHair001.SK_FemaleHair001'"));
	if (SK_SWORDMANHAIR.Succeeded()) HairMeshAsset = SK_SWORDMANHAIR.Object;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_SWORD(TEXT("SkeletalMesh'/Game/Resources/Characters/PlayerCharacters/StylizedSwordman/Weapons/SK_Sword.SK_Sword'"));
	if (SK_SWORD.Succeeded()) WeaponMeshAsset = SK_SWORD.Object;

	static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> PLAYER_ANIM_INSTANCE(TEXT("AnimBlueprint'/Game/Resources/Blueprints/Character/PlayerCharacter/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C'"));
	if (PLAYER_ANIM_INSTANCE.Succeeded()) PlayerCharacterAnimClass = PLAYER_ANIM_INSTANCE.Class;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_SKILL_TEST(
		TEXT("AnimMontage'/Game/Resources/Characters/PlayerCharacters/StylizedSwordman/Characters/Animations/Female/AM_SkillTest.AM_SkillTest'"));
	if (AM_SKILL_TEST.Succeeded())
		AnimMontageSkillTestAsset = AM_SKILL_TEST.Object;
}

void APlayerCharacter::InitializeComponets()
{
#pragma region Mesh Settings
	GetMesh()->SetSkeletalMesh(BodyMeshAsset);
	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_HAIR"));
	HairMesh->SetupAttachment(GetMesh(), TEXT("Hair_Socket"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_WEAPON"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("R_WeaponSocket"));

	HairMesh->SetSkeletalMesh(HairMeshAsset);
	WeaponMesh->SetSkeletalMesh(WeaponMeshAsset);
#pragma endregion

#pragma region Component Setting
	SpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	PlayerAttack = CreateDefaultSubobject<UPlayerAttackComponent>(TEXT("ATTACK"));
	PlayerInteraction = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("INTERACTION_COMPONENT"));
	PlayerInventory = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("PLAYERINVENTORY_COMPONENT"));
	PlayerWndController = CreateDefaultSubobject<UPlayerWndControllerComponent>(TEXT("PLAYER_WND_CONTROLLER"));
	MercenaryState = CreateDefaultSubobject<UMercenaryStateComponent>(TEXT("MERCENARY_STATE"));

	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);
	PlayerInteraction->SetupAttachment(GetRootComponent());
#pragma endregion

#pragma region Animation Setting
	if (IsValid(PlayerCharacterAnimClass))
	{
		GetMesh()->SetAnimInstanceClass(PlayerCharacterAnimClass);
	}
#pragma endregion
}

#pragma region InputBindAxis
void APlayerCharacter::InputHorizontal(float axis)
{
	if (IsMoveable())
	{
		HorizontalInputAxis = axis;
		FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(rightVector, axis);
	}
}

void APlayerCharacter::InputVertical(float axis)
{
	if (IsMoveable())
	{
		VerticalInputAxis = axis;
		FRotator yawRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(forwardVector, axis);
	}
}

#pragma endregion

#pragma region State
void APlayerCharacter::Jump()
{
	Super::Jump();
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
}
void APlayerCharacter::Run()
{
	if (IsMoveable())
		GetCharacterMovement()->MaxWalkSpeed = GetPlayerManager()->GetPlayerInfo()->RunSpeed;
}
void APlayerCharacter::Walk()
{
	if (!IsMoveKeyPressed())
		GetCharacterMovement()->MaxWalkSpeed = GetPlayerManager()->GetPlayerInfo()->WalkSpeed;
}

void APlayerCharacter::Dash()
{
	if (IsMoveable())
	{
		if (DashDelay >= GetWorld()->GetTimeSeconds() - LastDashTime) return;

		LastDashTime = GetWorld()->GetTimeSeconds();
		GetCharacterMovement()->AddImpulse(GetActorForwardVector() * 10000, true);
	}
}

void APlayerCharacter::SkillTest()
{
	PlayAnimMontage(AnimMontageSkillTestAsset, 1.0f);
}
void APlayerCharacter::LookatControlDirection()
{
	FRotator controlRotation = GetControlRotation();
	controlRotation.Roll = controlRotation.Pitch = 0.0f;

	SetActorRotation(controlRotation);
}

void APlayerCharacter::PlayerAttackMove(FVector direction, float power)
{
	GetCharacterMovement()->AddImpulse(direction * power, true);
}

void APlayerCharacter::UpdateEquipItemState(bool bUpdateAll, EEquipItemType updateItemType)
{
	if (bUpdateAll)
	{
		PlayerInventory->UpdateEquipItemState(EEquipItemType::EI_Weapon);
		PlayerInventory->UpdateEquipItemState(EEquipItemType::EI_Armor);
	}
	else
		PlayerInventory->UpdateEquipItemState(updateItemType);

	PlayerController->GetPlayerCharacterWidgetInstance()->UpdateHp();
}

bool APlayerCharacter::IsMoveable() const
{
	return bIsMoveable &&
		(!IsInAir())
		&& (!PlayerAttack->LRegularAttacking())
	    && (!PlayerAttack->RRegularAttacking());
}
UPlayerManager* APlayerCharacter::GetPlayerManager()
{
	return PlayerManager = (IsValid(PlayerManager)) ? PlayerManager :
		Cast<UFRGameInstance>(GetGameInstance())->
		GetManagerClass<UPlayerManager>();
}
#pragma endregion
