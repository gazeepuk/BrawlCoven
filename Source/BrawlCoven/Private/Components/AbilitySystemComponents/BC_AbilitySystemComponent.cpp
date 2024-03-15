// Ivan Piankouski / GazeePuk


#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"

void UBC_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBC_AbilitySystemComponent::OnEffectApplied);
}

void UBC_AbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                 FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

	for (const FGameplayTag& Tag : TagContainer)
	{
		const FString DebugMessage = FString::Printf(TEXT("GE Tag applied: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
	}
}
