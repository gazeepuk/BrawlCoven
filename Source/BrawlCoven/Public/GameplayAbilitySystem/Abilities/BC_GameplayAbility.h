// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BC_GameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAbilityTargetType : uint8
{
	EAT_SingleTarget,
	EAT_MultiTarget
};

UENUM(BlueprintType)
enum class EAbilityActionType : uint8
{
	EAA_Attack,
	EAA_Buff,
	EAA_Debuff,
};

/**
 * 
 */
UCLASS(BlueprintType)
class BRAWLCOVEN_API UBC_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)	
	EAbilityTargetType GetAbilityTargetType() const { return AbilityTargetType; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	EAbilityActionType GetAbilityActionType() const { return AbilityActionType; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTexture2D* GetAbilityIcon() const{return EffectIcon;}
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> AbilityEffectClass;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle AbilityEffectSpecHandle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	const TObjectPtr<UTexture2D> EffectIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAbilityTargetType AbilityTargetType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EAbilityActionType AbilityActionType;
private:
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
};
