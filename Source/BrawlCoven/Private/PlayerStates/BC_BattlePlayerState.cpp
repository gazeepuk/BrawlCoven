// Ivan Piankouski / GazeePuk


#include "PlayerStates/BC_BattlePlayerState.h"

#include "AbilitySystemComponent.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Net/UnrealNetwork.h"

ABC_BattlePlayerState::ABC_BattlePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBC_WarriorAttributeSet>("AttributeSet"); 
}

void ABC_BattlePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABC_BattlePlayerState, Level);
}

UAbilitySystemComponent* ABC_BattlePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABC_BattlePlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void ABC_BattlePlayerState::OnRep_Level(uint8 OldLevel)
{
}
