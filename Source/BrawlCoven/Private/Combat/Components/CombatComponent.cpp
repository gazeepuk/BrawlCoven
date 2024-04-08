// Ivan Piankouski / GazeePuk


#include "Combat/Components/CombatComponent.h"

#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	const ABC_WarriorBase* WarriorOwner = GetOwner<ABC_WarriorBase>();

	BC_AttributeSet = CastChecked<UBC_WarriorAttributeSet>(WarriorOwner->GetAttributeSet());

	ActionSpeed = InitActionSpeed = BC_AttributeSet->GetSpeed();
	checkf(ActionSpeed > 0, TEXT("AttributeSet Speed <= 0"))
}

void UCombatComponent::DecreaseActionSpeed(float InSubtractionValue)
{
	ActionSpeed -= InSubtractionValue;
	if (ActionSpeed < 0)
	{
		ActionSpeed += InitActionSpeed;
	}
}

void UCombatComponent::StartWarriorTurn()
{
}

void UCombatComponent::EndWarriorTurn()
{
	ActionSpeed = InitActionSpeed;
}
