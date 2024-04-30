// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BC_GameModeBase.h"
#include "BC_BattleGameModeBase.generated.h"

class ABC_WarriorBase;
class UBattleComponent;
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
	void SubtractActionSpeedForAllWarriors(float SubtractingValue);
	void EndPlayerTurn();
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
	//Battle
	TArray<TSoftObjectPtr<ABattlePosition>> BattlePositions1;
	TArray<TSoftObjectPtr<ABattlePosition>> BattlePositions2;

	//Players
	int32 PlayerInTurnIndex;
	UPROPERTY(BlueprintReadWrite, Category = "Players|States")
	TObjectPtr<ABC_BattlePlayerState> PlayerState1;
	UPROPERTY(BlueprintReadWrite, Category = "Players|States")
	TObjectPtr<ABC_BattlePlayerState> PlayerState2;

	UPROPERTY(BlueprintReadWrite, Category = "Players|Controllers")
	TObjectPtr<ABC_BattlePlayerController> PlayerController1;
	UPROPERTY(BlueprintReadWrite, Category = "Players|Controllers")
	TObjectPtr<ABC_BattlePlayerController> PlayerController2;
	UPROPERTY()
	TArray<TObjectPtr<ABC_BattlePlayerController>> PlayerControllers;
	
	TArray<TObjectPtr<ABC_WarriorBase>> AliveWarriors;

	FTimerHandle InitBattleHandle;
	
	ABC_WarriorBase* GetNextWarrior();
	ABC_BattlePlayerController* GetPlayerInTurnController(ABC_WarriorBase*& OutNextWarriorInTurn);
	ABC_BattlePlayerController* GetPlayerOutTurnController() const;

	void InitBattle();
	void StartBattle();
	bool IsReadyForNextTurn();
	void SetupBattlePositions();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SpawnWarriors(ABC_BattlePlayerController* InBattlePlayerController, const TArray<TSoftObjectPtr<ABattlePosition>>& InBattlePositions);
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SpawnWarriors(const FTransform& InWarriorTransform, ABC_WarriorBase*
	                                InWarriorToSpawn);
	void EndBattle();
	void StartTurn();
};
