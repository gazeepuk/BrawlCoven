// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "UI/WidgetControllers/BC_UserWidgetController.h"
#include "BC_WarriorCardWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, NewMaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateEnergyChanged, float, NewUltimateEnergy);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxUltimateEnergyChanged, float, NewMaxUltimateEnergy);

class ABC_WarriorBase;

/**
 * 
 */
UCLASS(BlueprintType)
class BRAWLCOVEN_API UBC_WarriorCardWidgetController : public UBC_UserWidgetController
{
	GENERATED_BODY()

public:
	virtual void SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams) override;
	void SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams, ABC_WarriorBase* InWarrior);
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "WidgetController|Delegates")
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "WidgetController|Delegates")
	FOnMaxHealthChanged OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "WidgetController|Delegates")
	FOnUltimateEnergyChanged OnUltimateEnergyChanged;
	UPROPERTY(BlueprintAssignable, Category = "WidgetController|Delegates")
	FOnMaxUltimateEnergyChanged OnMaxUltimateEnergyChanged;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController|Warrior")
	TObjectPtr<ABC_WarriorBase> Warrior;
};
