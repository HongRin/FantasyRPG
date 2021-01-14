#include "MercenaryWnd.h"


UMercenaryWnd::UMercenaryWnd(const FObjectInitializer& ObjInitializer)
	: Super(ObjInitializer)
{

}
void UMercenaryWnd::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateWndSize(700.0f, 600.0f);
}
