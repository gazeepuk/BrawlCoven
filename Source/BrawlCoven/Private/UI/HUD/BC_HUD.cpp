// Ivan Piankouski / GazeePuk


#include "UI/HUD/BC_HUD.h"

#include "Blueprint/UserWidget.h"
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

void ABC_HUD::BeginPlay()
{
	Super::BeginPlay();

	OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();

	
}
