#include "MercenaryShopWnd.h"

UMercenaryShopWnd::UMercenaryShopWnd(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{

}

void UMercenaryShopWnd::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateWndSize(700.0f, 600.0f);
}
