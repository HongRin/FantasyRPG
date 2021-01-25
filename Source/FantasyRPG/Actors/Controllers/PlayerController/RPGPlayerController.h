#pragma once

#include "FantasyRPG.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

UCLASS()
class FANTASYRPG_API ARPGPlayerController : public APlayerController,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UClosableWndControllerComponent* ClosableWndController;

	TSubclassOf<class UPlayerCharacterWidget> GameWidgetClass;
	class UPlayerCharacterWidget* PlayerCharacterWidgetInstance;

	FGenericTeamId TeamId;


public :
	ARPGPlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

private:
	void InputMouseX(float axis);
	void InputMouseY(float axis);

public :
	class UPlayerCharacterWidget* GetPlayerCharacterWidgetInstance();

	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override
	{ this->TeamId = TeamID; }
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override
	{ return TeamId; }

	FORCEINLINE class UClosableWndControllerComponent* GetClosableWndControllerComponent() const
	{
		return ClosableWndController;
	}

	FORCEINLINE class UPlayerCharacterWidget* GetPlayerCharacterWidgetInstance() const
	{
		return PlayerCharacterWidgetInstance;
	}

	void ChangeViewTarget(class AActor* newViewTarget);

	
};
