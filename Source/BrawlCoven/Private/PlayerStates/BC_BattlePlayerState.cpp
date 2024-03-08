// Ivan Piankouski / GazeePuk


#include "PlayerStates/BC_BattlePlayerState.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"

ABC_BattlePlayerState::ABC_BattlePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBC_WarriorAttributeSet>("AttributeSet"); 
}

UAbilitySystemComponent* ABC_BattlePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABC_BattlePlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
