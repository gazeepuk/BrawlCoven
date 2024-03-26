// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Battle.generated.h"

class ABC_WarriorBase;
/**
 * 
 */
UCLASS()
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
	
	TArray<TObjectPtr<ABC_WarriorBase>> TurnOrder;
	TObjectPtr<ABC_WarriorBase> Warrior1;
	TObjectPtr<ABC_WarriorBase> Warrior2;
};
