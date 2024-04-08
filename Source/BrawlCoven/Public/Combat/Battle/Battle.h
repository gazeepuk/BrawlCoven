// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "UObject/NoExportTypes.h"
#include "Battle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWarriorEndTurn, float, SubtractionValue);

class UFieldCard;
class ABC_BattlePlayerController;
class ABattlePosition;
class ABC_WarriorBase;

USTRUCT()
struct FBattleInitInfo
{
	GENERATED_BODY()

	TObjectPtr<ABC_BattlePlayerController> Player1;
	TObjectPtr<ABC_BattlePlayerController> Player2;

	TSubclassOf<ABC_WarriorBase> WarriorClass1;
	TSubclassOf<ABC_WarriorBase> WarriorClass2;

	TSubclassOf<UFieldCard> FieldCard1;
	TSubclassOf<UFieldCard> FieldCard2;
};

/**
 * 
 */
UCLASS(BlueprintType)
class BRAWLCOVEN_API UBattle : public UObject
{
	GENERATED_BODY()

public:
	void InitBattle(const FBattleInitInfo& BattleInitInfo);

	UFUNCTION()
	void StartTurn();
	
	bool IsReadyForNextTurn() const;

	UFUNCTION()
	void SetReadyForNextTurn();

	FOnWarriorEndTurn OnWarriorEndTurn;
private:
	
	//BattleInfo
	bool bReadyForNextTurn = true;
	
	//PlayerControllers
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_BattlePlayerController> Player1;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_BattlePlayerController> Player2;

	//BattlePositions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Battle|Properies")
	TArray<ABattlePosition*> Player1BattlePositions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Battle|Properies")
	TArray<ABattlePosition*> Player2BattlePositions;

	//Warriors
	UPROPERTY()
	TArray<TObjectPtr<ABC_WarriorBase>> AliveWarriors;

	TObjectPtr<ABC_WarriorBase> GetNextTurnWarrior();
	void SpawnWarriors(ABC_BattlePlayerController* PlayerController, TArray<ABattlePosition*> BattlePositions);
};
