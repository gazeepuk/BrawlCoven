// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
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
class BRAWLCOVEN_API UGameCard : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameCard Info")
	FText GetGameCardName() const { return GameCardName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameCard Info")
	FText GetGameCardDescription() const { return GameCardDescription; }

	UFUNCTION(BlueprintCallable)
	virtual void UseGameCard(const UAbilitySystemComponent* TargetASC, const UAbilitySystemComponent* SourceASC);

	virtual bool IsCardValid() { return GameCardAbility != nullptr; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "GameCard Info")
	FText GameCardName;
	UPROPERTY(BlueprintReadOnly, Category = "GameCard Info")
	FText GameCardDescription;

	UPROPERTY(EditDefaultsOnly, Category = "GameCard Info")
	TObjectPtr<UGameplayEffect> ApplyingAttributesEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBC_GameplayAbility> GameCardAbility;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
