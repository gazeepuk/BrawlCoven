// Ivan Piankouski / GazeePuk


#include "UI/WidgetControllers/BC_WarriorCardWidgetController.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"

void UBC_WarriorCardWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams)
{
	Super::SetWidgetControllerParams(InWidgetControllerParams);
}

void UBC_WarriorCardWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams,
	ABC_WarriorBase* InWarrior)
{
	Warrior = InWarrior;
	SetWidgetControllerParams(InWidgetControllerParams);
}

void UBC_WarriorCardWidgetController::BroadcastInitialValues()
{
	check(Warrior);
	const UBC_WarriorAttributeSet* WarriorAttributeSet = Cast<UBC_WarriorAttributeSet>(Warrior->GetAttributeSet());
	if(!WarriorAttributeSet)
	{
		WarriorAttributeSet = CastChecked<UBC_WarriorAttributeSet>(AttributeSet);
	}
	
	OnMaxHealthChanged.Broadcast(WarriorAttributeSet->GetMaxHealth());
	OnHealthChanged.Broadcast(WarriorAttributeSet->GetHealth());
	OnMaxUltimateEnergyChanged.Broadcast(WarriorAttributeSet->GetMaxUltimateEnergy());
	OnUltimateEnergyChanged.Broadcast(WarriorAttributeSet->GetUltimateEnergy());
}

