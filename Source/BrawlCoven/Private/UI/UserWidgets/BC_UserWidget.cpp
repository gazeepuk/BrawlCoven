// Ivan Piankouski / GazeePuk


#include "UI/UserWidgets/BC_UserWidget.h"

void UBC_UserWidget::SetWidgetController(UBC_UserWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
