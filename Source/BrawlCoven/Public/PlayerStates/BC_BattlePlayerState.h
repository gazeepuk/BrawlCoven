// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PlayerStates/BC_PlayerStateBase.h"
#include "BC_BattlePlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_BattlePlayerState : public ABC_PlayerStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABC_BattlePlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	
	FORCEINLINE uint8 GetPlayerLevel() const { return Level; }
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	uint8 Level = 1;
	UFUNCTION()
	void OnRep_Level(uint8 OldLevel);
};
