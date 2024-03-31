// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle.generated.h"

class ABattlePosition;
class ABC_WarriorBase;
/**
 * 
 */
UCLASS(BlueprintType)
class BRAWLCOVEN_API UBattle : public UObject
{
	GENERATED_BODY()

public:
	void InitBattle(ABC_WarriorBase* PlayerWarrior1, ABC_WarriorBase* PlayerWarrior2);

	UFUNCTION()
	void TurnRequest(ABC_WarriorBase* Warrior);
	UFUNCTION()
	void StartTurn();

	bool IsReadyForNextTurn() const;

	UFUNCTION()
	void SetReadyForNextTurn();

private:
	bool bReadyForNextTurn = true;
	UPROPERTY()
	TArray<TObjectPtr<ABC_WarriorBase>> TurnOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Battle Properies")
	TObjectPtr<ABattlePosition> BattlePosition1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Battle Properies")
	TObjectPtr<ABattlePosition> BattlePosition2;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_WarriorBase> Warrior1;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABC_WarriorBase> Warrior2;
};
