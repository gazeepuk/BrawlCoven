// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameCards/GameCard.h"
#include "FieldCard.generated.h"

/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UFieldCard : public UGameCard
{
	GENERATED_BODY()
public:
	UFieldCard();
	
	virtual bool IsCardValid() override;
	virtual void UseGameCard(const UAbilitySystemComponent* SourceASC, const UAbilitySystemComponent* TargetASC) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual const UAttributeSet* GetAttributeSet() const override;
	virtual uint8 GetPlayerLevel() override;
	
};
