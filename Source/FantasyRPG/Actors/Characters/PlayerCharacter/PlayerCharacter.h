// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actors/Characters/BaseCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "Structures/Player/PlayerInfo.h"
#include "Enums/EquipItemType.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FANTASYRPG_API APlayerCharacter : public ABaseCharacter,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private :

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UZoomableSpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* HairMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	class UPlayerAttackComponent* PlayerAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact", meta = (AllowPrivateAccess = "true"))
	class UPlayerInteractionComponent* PlayerInteraction;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class UPlayerInventoryComponent* PlayerInventory;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerWndController", meta = (AllowPrivateAccess = "true"))
	class UPlayerWndControllerComponent* PlayerWndController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerWndController", meta = (AllowPrivateAccess = "true"))
	class UMercenaryStateComponent* MercenaryState;
#pragma endregion

#pragma region SKeletalMeshes
	class USkeletalMesh* BodyMeshAsset;
	class USkeletalMesh* HairMeshAsset;
	class USkeletalMesh* WeaponMeshAsset;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		float Hp;


	UPROPERTY()
	class UPlayerManager* PlayerManager;

	TSubclassOf<class UPlayerAnimInstance> PlayerCharacterAnimClass;

	FGenericTeamId TeamId;

	class ARPGPlayerController* PlayerController;

#pragma region SkillTest
private :
	// 스킬 테스트용
	UPROPERTY()
	class UAnimMontage* AnimMontageSkillTestAsset;
	// 테스트용
	void SkillTest();
#pragma endregion

#pragma region State Variable
private :
	float HorizontalInputAxis;

	float VerticalInputAxis;

	float DashDelay;

	float LastDashTime;

	bool bIsMoveable;

	bool bIsRunState;
#pragma endregion
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser) override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual float GetMaxHp() override;
	virtual float GetHp() override;
	virtual void SetHp(float value) override;

private :
	void LoadAsset();
	void InitializeComponets();


private :
	void InputHorizontal(float axis);
	void InputVertical(float axis);

#pragma region State Function
public :
	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit) override;
private:
	void Run();
	void Walk();
	void Dash();
#pragma endregion

public :
	void LookatControlDirection();

	void PlayerAttackMove(FVector direction, float power);

	// 캐릭터의 능력치를 업데이트 합니다.
	void UpdateEquipItemState(bool bUpdateAll, EEquipItemType updateItemType = EEquipItemType::EI_Weapon);

public :
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override 
	{ this->TeamId = TeamID; }
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override 
	{ return TeamId; }

	FORCEINLINE UPlayerAttackComponent* GetPlayerAttack() const
	{return PlayerAttack;}

	FORCEINLINE class UCameraComponent* GetCameraComponent() const
	{ return Camera; }

	FORCEINLINE float GetHorizontalInputAxis() const
	{ return HorizontalInputAxis; }

	FORCEINLINE float GetVerticalInputAxis() const
	{ return VerticalInputAxis; }

	bool IsMoveable() const;

	FORCEINLINE void ProhibitMove()
	{
		bIsMoveable = false;
	}

	FORCEINLINE void AllowMove()
	{
		bIsMoveable = true;
	}

	FORCEINLINE bool IsMoveKeyPressed() const
	{ 
		return (FMath::Abs(GetHorizontalInputAxis()) > 0.01f) ||
		(FMath::Abs(GetVerticalInputAxis()) > 0.01f);
	}

	FORCEINLINE bool IsInAir() const
	{ return GetCharacterMovement()->IsFalling(); }

	FORCEINLINE bool IsDoblueJump() const
	{ return JumpCurrentCount == 2; }

	class UPlayerManager* GetPlayerManager();

	FORCEINLINE class ARPGPlayerController* GetPlayerController() const
	{ return PlayerController; }

	FORCEINLINE class UPlayerInventoryComponent* GetPlayerInventory() const
	{ return PlayerInventory; }

	FORCEINLINE class UMercenaryStateComponent* GetMercenaryState() const
	{ return MercenaryState; }
};
