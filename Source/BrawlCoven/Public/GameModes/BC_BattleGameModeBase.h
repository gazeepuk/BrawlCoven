// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameModes/BC_GameModeBase.h"
#include "BC_BattleGameModeBase.generated.h"

class UBC_WarriorAttributeSet;
class UAbilitySystemComponent;
class ABC_BattlePlayerState;
class ABC_PlayerStateBase;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_BattleGameModeBase : public ABC_GameModeBase
{
	GENERATED_BODY()
public:
	ABC_BattleGameModeBase();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UBC_WarriorAttributeSet> AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitStatsGameplayEffectClass;
	
	UPROPERTY()
	TObjectPtr<ABC_BattlePlayerState> Player1;
	UPROPERTY()
	TObjectPtr<ABC_BattlePlayerState> Player2;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
};
