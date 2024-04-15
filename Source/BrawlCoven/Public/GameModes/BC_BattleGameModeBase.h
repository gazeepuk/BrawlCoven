// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameModes/BC_GameModeBase.h"
#include "BC_BattleGameModeBase.generated.h"

class ABattle;
class ABC_BattlePlayerController;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void OnRep_ActiveBattle();
protected:
	virtual void BeginPlay() override;

	//GameplayAbilitySystem
	/*UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UBC_WarriorAttributeSet> AttributeSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitStatsGameplayEffectClass;*/

	//Battle
	UPROPERTY(BlueprintReadWrite, Category = "Battle", Replicated = OnRep_ActiveBattle)
	ABattle* ActiveBattle = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle")
	TSoftObjectPtr<ABattlePosition> BattlePosition1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle")
	TSoftObjectPtr<ABattlePosition> BattlePosition2;

	//Players
	UPROPERTY(BlueprintReadWrite, Category = "Players|States")
	TObjectPtr<ABC_BattlePlayerState> PlayerState1;
	UPROPERTY(BlueprintReadWrite, Category = "Players|Controllers")
	TObjectPtr<ABC_BattlePlayerController> PlayerController1;
	UPROPERTY(BlueprintReadWrite, Category = "Players|States")
	TObjectPtr<ABC_BattlePlayerState> PlayerState2;
	UPROPERTY(BlueprintReadWrite, Category = "Players|Controllers")
	TObjectPtr<ABC_BattlePlayerController> PlayerController2;
	
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayersInitialized();
};
