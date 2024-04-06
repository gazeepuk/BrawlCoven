// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameModes/BC_GameModeBase.h"
#include "BC_BattleGameModeBase.generated.h"

class ABattlePosition;
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

	//GameplayAbilitySystem
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UBC_WarriorAttributeSet> AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitStatsGameplayEffectClass;

	//Battle
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle")
	TSoftObjectPtr<ABattlePosition> BattlePosition1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle")
	TSoftObjectPtr<ABattlePosition> BattlePosition2;

	//Players
	UPROPERTY()
	TObjectPtr<ABC_BattlePlayerState> Player1;
	UPROPERTY()
	TObjectPtr<ABC_BattlePlayerState> Player2;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
};
