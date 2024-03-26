// Ivan Piankouski / GazeePuk


#include "Combat/Battle/Battle.h"

#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Combat/Components/CombatComponent.h"

void UBattle::InitBattle(ABC_WarriorBase* PlayerWarrior1, ABC_WarriorBase* PlayerWarrior2)
{
	Warrior1 = PlayerWarrior1;
	Warrior2 = PlayerWarrior2;
}

void UBattle::TurnRequest(ABC_WarriorBase* Warrior)
{
	TurnOrder.AddUnique(Warrior);
	StartTurn();
}

void UBattle::StartTurn()
{
	if (!IsReadyForNextTurn())
	{
		return;
	}
	bReadyForNextTurn = false;

	const ABC_WarriorBase* ActiveWarrior = TurnOrder[0];

	UCombatComponent* CombatComponent = ActiveWarrior->GetComponentByClass<UCombatComponent>();
	check(CombatComponent);

	CombatComponent->StartWarriorTurn();
	CombatComponent->OnTurnEnded.AddUniqueDynamic(this, &UBattle::SetReadyForNextTurn);
	TurnOrder.RemoveAt(0);
}

bool UBattle::IsReadyForNextTurn() const
{
	return TurnOrder.IsValidIndex(0) && bReadyForNextTurn;
}

void UBattle::SetReadyForNextTurn()
{
	bReadyForNextTurn = true;

	if (IsReadyForNextTurn())
	{
		StartTurn();
	}
}
