// Ivan Piankouski / GazeePuk


#include "Combat/Battle/Battle.h"
#include "Combat/Battle/BattlePosition.h"

#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Combat/Components/CombatComponent.h"
#include "PlayerControllers/BC_BattlePlayerController.h"

void UBattle::InitBattle(const FBattleInitInfo& BattleInitInfo)
{
	Player1 = BattleInitInfo.Player1;
	Player2 = BattleInitInfo.Player2;

	
	
	WarriorCycleDistances.Add(Warrior1, NextTurnDistance);
	WarriorCycleDistances.Add(Warrior2, NextTurnDistance);

	
}

void UBattle::StartTurn()
{
	if (!IsReadyForNextTurn())
	{
		return;
	}
	bReadyForNextTurn = false;

	ABC_WarriorBase* ActiveWarrior = GetNextTurnWarrior();

	UCombatComponent* CombatComponent = ActiveWarrior->GetComponentByClass<UCombatComponent>();
	check(CombatComponent);

	CombatComponent->StartWarriorTurn();


	PreviousWarrior = ActiveWarrior;
	CombatComponent->OnTurnEnded.AddUniqueDynamic(this, &UBattle::SetReadyForNextTurn);
}

bool UBattle::IsReadyForNextTurn() const
{
	return Warrior1->IsAlive() && Warrior2->IsAlive() && bReadyForNextTurn;
}

void UBattle::SetReadyForNextTurn()
{
	bReadyForNextTurn = true;

	if (IsReadyForNextTurn())
	{
		StartTurn();
	}
}

TObjectPtr<ABC_WarriorBase> UBattle::GetNextTurnWarrior()
{

	while(WarriorCycleDistances[Warrior1] > 0 && WarriorCycleDistances[Warrior2] > 0)
	{
		if(Warrior1 != PreviousWarrior)
		{
			WarriorCycleDistances.FindChecked(Warrior1) -= Warrior1->GetSpeed();
		}
		if(Warrior2 != PreviousWarrior)
		{
			WarriorCycleDistances.FindChecked(Warrior2) -= Warrior2->GetSpeed();
		}
	}

	
	if(Warrior1 != PreviousWarrior)
	{
		WarriorCycleDistances.FindChecked(Warrior1) += WarriorCycleDistances.FindChecked(Warrior1) < 0 ? NextTurnDistance : 0;
	}
	if(Warrior2 != PreviousWarrior)
	{
		WarriorCycleDistances.FindChecked(Warrior2) += WarriorCycleDistances.FindChecked(Warrior2) < 0 ? NextTurnDistance : 0;
	}
	
	const TObjectPtr<ABC_WarriorBase> NextWarrior = Warrior1->GetSpeed() < Warrior2->GetSpeed() ? Warrior1 : Warrior2;
	
	return NextWarrior;
}
