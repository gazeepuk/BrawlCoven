// Ivan Piankouski / GazeePuk


#include "UI/UserWidgets/Cards/BC_CardWidget.h"
#include "Components/Button.h"
#include "Components/SizeBoxSlot.h"
void UBC_CardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CardButton)
	{
		CardButton->OnClicked.AddDynamic(this, &UBC_CardWidget::OnButtonClicked);
	}
}
