// Ivan Piankouski / GazeePuk


#include "GameCards/AbilityCard.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStates/BC_BattlePlayerState.h"

UAbilityCard::UAbilityCard()
{
	if(GetWorld())
	{
		OwningPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ABC_BattlePlayerState>();
	}
}

UAbilitySystemComponent* UAbilityCard::GetAbilitySystemComponent() const
{
	check(OwningPlayer);
	return OwningPlayer->GetAbilitySystemComponent();
}

const UAttributeSet* UAbilityCard::GetAttributeSet() const
{
	return GetAbilitySystemComponent()->GetAttributeSet(UBC_WarriorAttributeSet::StaticClass());
}

uint8 UAbilityCard::GetPlayerLevel()
{
	check(OwningPlayer)
	return OwningPlayer->GetPlayerLevel();
}

