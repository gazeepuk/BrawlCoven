// Ivan Piankouski / GazeePuk


#include "GameCards/GameCard.h"

void UGameCard::UseGameCard(const UAbilitySystemComponent* SourceASC, const UAbilitySystemComponent* TargetASC)
{
	check(IsCardValid())
}


UAbilitySystemComponent* UGameCard::GetAbilitySystemComponent() const
{
	return nullptr;
}

const UAttributeSet* UGameCard::GetAttributeSet() const
{
	return nullptr;
}
