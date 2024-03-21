// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BC_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void SetTargetASC(UAbilitySystemComponent* InTargetASC) { TargetASC = InTargetASC; }

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> AbilityEffectClass;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle AbilityEffectSpecHandle;

private:
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
};
