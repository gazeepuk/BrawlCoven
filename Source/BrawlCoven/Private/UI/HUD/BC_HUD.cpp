// Ivan Piankouski / GazeePuk


#include "UI/HUD/BC_HUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/UserWidgets/BC_UserWidget.h"
#include "UI/UserWidgets/Cards/BC_CardWidget.h"
#include "UI/WidgetControllers/BC_UserWidgetController.h"
#include "UI/WidgetControllers/BC_WarriorCardWidgetController.h"

UBC_UserWidgetController* ABC_HUD::GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
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

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidget->AddToViewport();
}

UBC_WarriorCardWidgetController* ABC_HUD::GetWarriorCardWidgetController(
	const FWidgetControllerParams& InWidgetControllerParams, ABC_WarriorBase* InWarrior)
{
	check(WarriorCardWidgetClass)
	UBC_WarriorCardWidgetController* WarriorCardWidgetController = NewObject<UBC_WarriorCardWidgetController>(this, WarriorCardWidgetControllerClass);

	WarriorCardWidgetController->SetWidgetControllerParams(InWidgetControllerParams, InWarrior);
	return WarriorCardWidgetController;
}

UBC_CardWidget* ABC_HUD::InitWarriorCard(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS,
                              ABC_WarriorBase* InWarrior)
{
	check(WarriorCardWidgetClass);
	check(WarriorCardWidgetControllerClass);
	UBC_CardWidget* WarriorCardWidget = CreateWidget<UBC_CardWidget>(GetWorld(), WarriorCardWidgetClass);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UBC_WarriorCardWidgetController* WarriorCardWidgetController = GetWarriorCardWidgetController(WidgetControllerParams, InWarrior);

	WarriorCardWidget->SetWidgetController(WarriorCardWidgetController);
	return WarriorCardWidget;
}