// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "BattleComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWarriorEndTurn, float, SubtractionValue);

class UFieldCard;
class ABC_BattlePlayerController;
class ABattlePosition;
class ABC_WarriorBase;

/**
 * 
 */
UCLASS(BlueprintType)
class BRAWLCOVEN_API UBattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void InitBattle(ABC_BattlePlayerController* PlayerController1, ABC_BattlePlayerController* PlayerController2);

	UFUNCTION(Reliable, Client)
	void StartTurn_Client();

	UFUNCTION()
	bool IsReadyForNextTurn() const;

	UFUNCTION()
	void SetReadyForNextTurn();

	FOnWarriorEndTurn OnWarriorEndTurn;
private:
	//BattleInfo
	bool bReadyForNextTurn = true;
	
	//PlayerControllers
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_BattlePlayerController> Player1;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_BattlePlayerController> Player2;

	//BattlePositions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ExposeOnSpawn), Category = "Battle|Properies")
	TArray<TSoftObjectPtr<ABattlePosition>> Player1BattlePositions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ExposeOnSpawn), Category = "Battle|Properies")
	TArray<TSoftObjectPtr<ABattlePosition>> Player2BattlePositions;

	//Warriors
	UPROPERTY()
	TArray<TObjectPtr<ABC_WarriorBase>> AliveWarriors;

	TObjectPtr<ABC_WarriorBase> GetNextTurnWarrior();

	
	UFUNCTION(Reliable, Server, WithValidation)
	FORCEINLINE
	void SpawnWarriors_Server(ABC_BattlePlayerController* PlayerController, const TArray<TSoftObjectPtr<ABattlePosition>>& BattlePositions);
	UFUNCTION(Unreliable, Client)
	FORCEINLINE
	void SpawnWarriors_Client(const TArray<TSubclassOf<ABC_WarriorBase>>& WarriorClasses, const TArray<ABattlePosition*>& BattlePositions, ABC_BattlePlayerController* OwningPlayerController);
};
