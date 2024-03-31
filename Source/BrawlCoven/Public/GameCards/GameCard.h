// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Combat/CombatInterface.h"
#include "UObject/NoExportTypes.h"
#include "GameCard.generated.h"

class UAttributeSet;
class UGameplayEffect;
class UAbilitySystemComponent;
class UBC_GameplayAbility;
class UAbilityCard;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UGameCard : public UObject, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameCard Info")
	FText GetGameCardName() const { return GameCardName; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameCard Info")
	FText GetGameCardDescription() const { return GameCardDescription; }

	UFUNCTION(BlueprintCallable)
	virtual void UseGameCard(const UAbilitySystemComponent* SourceASC, const UAbilitySystemComponent* TargetASC);

	virtual bool IsCardValid() { return GameCardAbility != nullptr; }

	UFUNCTION(BlueprintGetter)
	virtual uint8 GetPlayerLevel() override;
	UFUNCTION(BlueprintGetter, Category = "Gameplay Ability System")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintGetter, Category = "Gameplay Ability System")
	virtual const UAttributeSet* GetAttributeSet() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "GameCard Info")
	FText GameCardName;
	UPROPERTY(BlueprintReadOnly, Category = "GameCard Info")
	FText GameCardDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameCard Info")
	TObjectPtr<UBC_GameplayAbility> GameCardAbility;

};
