// Ivan Piankouski / GazeePuk


#include "GameCards/FieldCard.h"

#include "AbilitySystemComponent.h"

UFieldCard::UFieldCard()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Mixed;
}

bool UFieldCard::IsCardValid()
{
	return false;		
}

void UFieldCard::UseGameCard(const UAbilitySystemComponent* TargetASC, const UAbilitySystemComponent* SourceASC)
{
	Super::UseGameCard(TargetASC, SourceASC);
}
