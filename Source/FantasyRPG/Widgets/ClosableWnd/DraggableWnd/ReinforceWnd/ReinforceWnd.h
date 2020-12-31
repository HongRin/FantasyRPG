#pragma once

#include "CoreMinimal.h"
#include "Widgets/ClosableWnd/DraggableWnd/DraggableWnd.h"
#include "Enums/ReinforceResult.h"
#include "ReinforceWnd.generated.h"

UCLASS()
class FANTASYRPG_API UReinforceWnd : public UDraggableWnd
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	// ��ȭ�� ������ �� ȣ��Ǵ� �������Ʈ �̺�Ʈ�Դϴ�.
	/// - �������Ʈ �̺�Ʈ�� cpp �� �������� �ʽ��ϴ�.
	UFUNCTION(BlueprintImplementableEvent, Category = "Reinforce Event")
		void OnReinforceFinished(EReinforceResult result);
};
