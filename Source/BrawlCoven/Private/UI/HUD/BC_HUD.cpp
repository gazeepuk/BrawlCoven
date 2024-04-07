// Ivan Piankouski / GazeePuk


#include "UI/HUD/BC_HUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/UserWidgets/BC_UserWidget.h"
#include "UI/WidgetControllers/BC_UserWidgetController.h"

UBC_UserWidgetController* ABC_HUD::GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UBC_UserWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(InWidgetControllerParams);
	}
	return OverlayWidgetController;
}

void ABC_HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlayWidgetClass);
	check(OverlayWidgetControllerClass);
	OverlayWidget = CreateWidget<UBC_UserWidget>(GetWorld(), OverlayWidgetClass);

	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(OverlayWidgetController);
	
	OverlayWidget->AddToViewport();
}

