#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClosableWnd.generated.h"


DECLARE_MULTICAST_DELEGATE(FWndEventSignature)

UCLASS()
class FANTASYRPG_API UClosableWnd : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FWndEventSignature onWndOpened;
	FWndEventSignature onWndClosed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Size")
		FVector2D WndSize;

protected:
	UPROPERTY()
		UClosableWnd* ParentWnd;

	UPROPERTY()
		TArray<UClosableWnd*> ChildWnds;

	UPROPERTY()
		class UButton* CloseButton;

	UPROPERTY()
		class UClosableWndControllerComponent* ClosableWndController;

protected:
	virtual void NativeConstruct() override;

public:
	void SetCloseButton(class UButton* closeButton);

	// �ڽ� â�� �����մϴ�.
	/// - ������ â�� ��ȯ�˴ϴ�.
	UFUNCTION(BlueprintCallable)
	UClosableWnd * CreateChildClosableWnd(TSubclassOf<UClosableWnd> closableWnd);

protected :
	// Ư���� â�� �Ҵ�Ǿ��ִ��� Ȯ���մϴ�.
	UFUNCTION(BlueprintCallable)
	bool IsAllocated(UClosableWnd* childwnd);

	// �ڽ� â�� �θ� â���� ���ܽ�ŵ�ϴ�.
	/// - �ش� �޼���� �ڽ� â�� �ݴ� ������ ���� ������, �迭 ChildWnds ���� ��Ҹ� �����ϱ⸸ �մϴ�.
	void RemoveFromParentWnd(UClosableWnd* childWnd);

public:
	UFUNCTION()
	void OnCloseButtonClicked();

public:
	FORCEINLINE void SetClosableWndContorller(class UClosableWndControllerComponent* closableWndController)
	{
		ClosableWndController = closableWndController;
	}

	void UpdateWndSize(float width, float height);
};
