// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BC_UserWidget.generated.h"

class UBC_UserWidgetController;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE
	UBC_UserWidgetController* GetWidgetController() const { return WidgetController; }

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UBC_UserWidgetController* InWidgetController);

protected:

	UPROPERTY(BlueprintReadonly)
	TObjectPtr<UBC_UserWidgetController> WidgetController;

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
