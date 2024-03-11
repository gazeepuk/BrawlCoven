// Ivan Piankouski / GazeePuk


#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"

void UBC_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBC_AbilitySystemComponent::OnEffectApplied);
}

void UBC_AbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                 FActiveGameplayEffectHandle ActiveEffectHandle)
{
}
