// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/Abilities/BC_GameplayAbility.h"
#include "BC_AbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsDelegate, const FGameplayTagContainer&);
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	FEffectAssetTagsDelegate EffectAssetTags;

	void AbilityActorInfoSet();
	void AddWarriorAbilities(const TArray<TSubclassOf<UBC_GameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
protected:
	void OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
