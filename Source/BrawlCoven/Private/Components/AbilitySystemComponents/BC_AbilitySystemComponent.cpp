// Ivan Piankouski / GazeePuk


#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"

#include "GameplayAbilitySystem/Abilities/BC_GameplayAbility.h"

void UBC_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBC_AbilitySystemComponent::OnEffectApplied);
}

void UBC_AbilitySystemComponent::AddWarriorAbilities(const TArray<TSubclassOf<UBC_GameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UBC_GameplayAbility>& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UBC_GameplayAbility* BCAbility = Cast<UBC_GameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(BCAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}

	}
}

void UBC_AbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid())
	{
		return;
	}

	for(FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if(!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UBC_AbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid())
	{
		return;
	}

	for(FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
			if(!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UBC_AbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
                                                 FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

	/*for (const FGameplayTag& Tag : TagContainer)
	{
		const FString DebugMessage = FString::Printf(TEXT("GE Tag applied: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
	}*/
}
