// Ivan Piankouski / GazeePuk


#include "UI/UserWidgets/Cards/BC_CardWidget.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Styling/SlateBrush.h"

void UBC_CardWidget::SetCardName(const FString& InCardNameString)
{
	CardName = FText::FromString(InCardNameString.TrimStartAndEnd());
	CardNameTextBlock->SetText(CardName);
}

void UBC_CardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CardButton)
	{
		CardButton->OnClicked.AddDynamic(this, &UBC_CardWidget::OnButtonClicked);
	}
}
