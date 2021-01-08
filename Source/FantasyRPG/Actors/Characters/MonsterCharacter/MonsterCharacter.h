#pragma once

#include "Actors/Characters/BaseCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "Structures/Monster/MonsterInfo.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class FANTASYRPG_API AMonsterCharacter : public ABaseCharacter,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UPlayerDetectorComponent* PlayerDetector;

	// Indicates an MonsterWidgetComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UMonsterWidgetComponent* MonsterWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UMonsterAttackComponent* MonsterAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	FName MonsterCode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float MonsterHpLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float Hp;

	// GameInstance
	UPROPERTY()
	class UFRGameInstance* GameInst;

	// Indicates an DataTableAsset
	UPROPERTY()
	class UDataTable* MonsterDatatable;

	FMonsterInfo MonsterInfo;

	FGenericTeamId TeamId;
public:
	AMonsterCharacter();


#pragma region Overrides...
protected:
	virtual void BeginPlay() override;


	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser) override;

	virtual void OnCharacterDie() override;
#pragma endregion
private :
	// Components Initialization
	void InitializeComponent();

	// SkeletalMeshInfomation Initialization
	void InitializeSkeletalMeshComponent();

public :
	// MonsterData Initialization
	UFUNCTION(BlueprintCallable)
	void InitializeMonsterDataConstructTime();

	// Rushes in the specified direction.
	void MonsterDash(FVector direction, float power);

	FORCEINLINE virtual float GetMaxHp() override
	{ return MaxHp; }
	FORCEINLINE virtual float GetHp() override
	{ return Hp; }
	FORCEINLINE virtual void SetHp(float value) override
	{ Hp = value; }

public :
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override
	{ this-> TeamId = TeamID; }
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override
	{ return TeamId; }

	FORCEINLINE UPlayerDetectorComponent* GetPlayerDetector() const
	{ return PlayerDetector; }

	FORCEINLINE UMonsterAttackComponent* GetMonsterAttack() const
	{ return MonsterAttack; }

	FORCEINLINE bool IsMovable() const;

	FORCEINLINE FMonsterInfo* GetMonsterInfo()
	{ return &MonsterInfo; }

};
