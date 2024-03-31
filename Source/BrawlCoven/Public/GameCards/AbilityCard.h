// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameCard.h"
#include "AbilityCard.generated.h"

class ABC_WarriorBase;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UAbilityCard : public UGameCard
{
	GENERATED_BODY()

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual const UAttributeSet* GetAttributeSet() const override;
	virtual uint8 GetPlayerLevel() override;
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABC_WarriorBase> OwningWarrior;
};
