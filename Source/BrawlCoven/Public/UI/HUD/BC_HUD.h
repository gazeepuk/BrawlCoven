// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetControllers/BC_UserWidgetController.h"
#include "BC_HUD.generated.h"

class UBC_CardWidget;
class ABC_WarriorBase;
class UBC_WarriorCardWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UBC_UserWidgetController;
class UBC_UserWidget;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintGetter)
	FORCEINLINE
	UBC_UserWidget* GetOverlayWidget() const { return OverlayWidget; }

	UBC_UserWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UBC_WarriorCardWidgetController* GetWarriorCardWidgetController(const FWidgetControllerParams& InWidgetControllerParams, ABC_WarriorBase* InWarrior);
	UBC_CardWidget* InitWarriorCard(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS, ABC_WarriorBase* InWarrior);
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<UBC_UserWidget> OverlayWidget;
	UPROPERTY(BlueprintReadWrite, Category = "WidgetControllers")
	TObjectPtr<UBC_UserWidgetController> OverlayWidgetController;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBC_UserWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WarriorCardWidgetClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBC_WarriorCardWidgetController> WarriorCardWidgetControllerClass;
};
