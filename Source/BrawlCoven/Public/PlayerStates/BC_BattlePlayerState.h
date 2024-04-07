// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "PlayerStates/BC_PlayerStateBase.h"
#include "BC_BattlePlayerState.generated.h"

class UBattleKitComponent;
class ABC_WarriorBase;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_BattlePlayerState : public ABC_PlayerStateBase
{
	GENERATED_BODY()

public:
	ABC_BattlePlayerState();
	
	FORCEINLINE TArray<ABC_WarriorBase*>& GetPlayerWarriors() { return PlayerWarriors; }
	void AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior) const;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle|Components")
	TObjectPtr<UBattleKitComponent> BattleKitComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Battle|Components")
	TArray<ABC_WarriorBase*> PlayerWarriors;
};
