// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle.generated.h"

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

private:
	
	//BattleInfo
	bool bReadyForNextTurn = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float NextTurnDistance = 100.f;
	UPROPERTY()
	TMap<TObjectPtr<ABC_WarriorBase>, float> WarriorCycleDistances;
	UPROPERTY()
	TArray<TSubclassOf<UFieldCard>> FieldCardClasses;
	//UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	
	
	//PlayerControllers
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_BattlePlayerController> Player1;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_BattlePlayerController> Player2;

	//BattlePositions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Battle Properies")
	TObjectPtr<ABattlePosition> BattlePosition1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Battle Properies")
	TObjectPtr<ABattlePosition> BattlePosition2;

	//Warriors
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_WarriorBase> Warrior1;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_WarriorBase> Warrior2;
	UPROPERTY()
	TObjectPtr<ABC_WarriorBase> PreviousWarrior;


	TObjectPtr<ABC_WarriorBase> GetNextTurnWarrior();
};
