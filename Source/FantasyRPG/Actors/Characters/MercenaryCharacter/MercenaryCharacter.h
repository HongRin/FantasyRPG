#pragma once

#include "Actors/Characters/BaseCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "Structures/MercenaryInfo/MercenaryInfo.h"
#include "MercenaryCharacter.generated.h"

UCLASS()
class FANTASYRPG_API AMercenaryCharacter : public ABaseCharacter ,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* HairMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* LeftWeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* RightWeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UPlayerDetectorComponent* PlayerDetector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	FName MercenaryCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UMercenaryAttackComponent* MercenaryAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UHealerBehaviorComponent* HealerBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float Hp;

	UPROPERTY()
	class UFRGameInstance* GameInst;

	UPROPERTY()
	class UDataTable* MercenaryDatatable;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	FMercenaryInfo MercenaryInfo;
	
	FGenericTeamId TeamId;

public :
	AMercenaryCharacter();

protected :
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser) override;

	virtual void OnCharacterDie() override;


private :
	// Components Initialization
	void InitializeComponent();

	// SkeletalMeshInfomation Initialization
	void InitializeSkeletalMeshComponent();

private :
	void SetMoveSpeed();

public :
	// MonsterData Initialization
	UFUNCTION(BlueprintCallable)
	void InitializeMercenaryDataConstructTime();

	void MercenaryDash(FVector direction, float power);

public :
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override
	{ this->TeamId = TeamID; }
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override
	{ return TeamId; }

	FORCEINLINE virtual float GetMaxHp() override
	{
		return MaxHp;
	}
	FORCEINLINE virtual float GetHp() override
	{
		return Hp;
	}
	FORCEINLINE virtual void SetHp(float value) override
	{
		Hp = value;
	}
	
	FORCEINLINE class UPlayerDetectorComponent* GetPlayerDetector() const
	{ return PlayerDetector; }

	FORCEINLINE class UMercenaryAttackComponent* GetMercenaryAttack() const
	{
		return MercenaryAttack;
	}

	FORCEINLINE class UHealerBehaviorComponent* GetHealerBehavior() const
	{
		return HealerBehavior;
	}

	bool IsMercenaryMovable() const;

	bool IsHealerMovable() const;

	FORCEINLINE FMercenaryInfo* GetMercenaryInfo()
	{ return &MercenaryInfo; }

	FORCEINLINE class APlayerCharacter* GetPlayerCharacter() const
	{ return PlayerCharacter; }
};
