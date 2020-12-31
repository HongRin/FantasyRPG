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

	// 자식 창을 생성합니다.
	/// - 생성된 창을 반환됩니다.
	UFUNCTION(BlueprintCallable)
	UClosableWnd * CreateChildClosableWnd(TSubclassOf<UClosableWnd> closableWnd);

protected :
	// 특정한 창이 할당되어있는지 확인합니다.
	UFUNCTION(BlueprintCallable)
	bool IsAllocated(UClosableWnd* childwnd);

	// 자식 창을 부모 창에서 제외시킵니다.
	/// - 해당 메서드는 자식 창을 닫는 역할을 하지 않으며, 배열 ChildWnds 에서 요소를 제거하기만 합니다.
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
