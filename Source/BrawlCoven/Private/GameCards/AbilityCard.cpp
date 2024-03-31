// Ivan Piankouski / GazeePuk


#include "GameCards/AbilityCard.h"

#include "AbilitySystemComponent.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"

UAbilitySystemComponent* UAbilityCard::GetAbilitySystemComponent() const
{
	check(OwningWarrior);
	return OwningWarrior->GetAbilitySystemComponent();
}

const UAttributeSet* UAbilityCard::GetAttributeSet() const
{
	return GetAbilitySystemComponent()->GetAttributeSet(UBC_WarriorAttributeSet::StaticClass());
}

uint8 UAbilityCard::GetPlayerLevel()
{
	check(OwningWarrior)
	return OwningWarrior->GetPlayerLevel();
}
