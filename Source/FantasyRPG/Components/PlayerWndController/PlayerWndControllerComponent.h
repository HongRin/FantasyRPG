#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerWndControllerComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASYRPG_API UPlayerWndControllerComponent : public UActorComponent
{
	GENERATED_BODY()


#pragma region Widgets
private:
	TSubclassOf<class UStatusWnd> BPStatusWndClass;
	TSubclassOf<class UInventoryWnd> BPInventoryWndClass;
	
private :
	class UStatusWnd* StatusWnd;
	class UInventoryWnd* InventoryWnd;

#pragma endregion

#pragma region Components
private :
	class UClosableWndControllerComponent* ClosableWndController;
	class UPlayerInventoryComponent* PlayerInventory;
#pragma endregion

private :
	struct FPlayerInfo* PlayerInfo;
	
public:	
	UPlayerWndControllerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	void OpenStatus();
	void CloseStatus();

	void OpenInventory();
	void CloseInventory();

public :
	// 인벤토리 창 열림 상태에 따라 인벤토리 창을 열거나 닫습니다.
	FORCEINLINE void ToggleStatus()
	{
		if (!IsStatusOpend()) OpenStatus();
		else CloseStatus();
	}

	FORCEINLINE bool IsStatusOpend() const
	{
		return StatusWnd != nullptr;
	}

	FORCEINLINE void ToggleInventory()
	{
		if (!IsInventoryOpend()) OpenInventory();
		else CloseInventory();
	}
	
	FORCEINLINE bool IsInventoryOpend() const
	{
		return InventoryWnd != nullptr;
	}
		
};
