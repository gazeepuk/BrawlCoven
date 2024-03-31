// Ivan Piankouski / GazeePuk


#include "GameCards/GameCard.h"

void UGameCard::UseGameCard(const UAbilitySystemComponent* SourceASC, const UAbilitySystemComponent* TargetASC)
{
	check(IsCardValid())
}

uint8 UGameCard::GetPlayerLevel()
{
	return ICombatInterface::GetPlayerLevel();
}

UAbilitySystemComponent* UGameCard::GetAbilitySystemComponent() const
{
	return nullptr;
}

const UAttributeSet* UGameCard::GetAttributeSet() const
{
	return nullptr;
}
