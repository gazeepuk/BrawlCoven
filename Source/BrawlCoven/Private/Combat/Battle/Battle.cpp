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

	//Spawning Warriors
	SpawnWarriors(Player1, Player1BattlePositions);
	SpawnWarriors(Player2, Player2BattlePositions);

	//Sort Warriors by ActionSpeed
	AliveWarriors.Sort([](const TObjectPtr<ABC_WarriorBase>& Warrior1, const TObjectPtr<ABC_WarriorBase>& Warrior2)
	{
		return Warrior1->GetActionSpeed() < Warrior2->GetActionSpeed();
	});

	//Subtracting first warrior action speed  
	const float FirstWarriorActionSpeed = AliveWarriors[0]->GetActionSpeed();
	
	for (auto It = AliveWarriors.CreateConstIterator(); It; ++It)
	{
		It->Get()->GetComponentByClass<UCombatComponent>()->DecreaseActionSpeed(FirstWarriorActionSpeed);
	}

	StartTurn();
}

void UBattle::StartTurn()
{
	if (!IsReadyForNextTurn())
	{
		return;
	}
	bReadyForNextTurn = false;

	const ABC_WarriorBase* ActiveWarrior = GetNextTurnWarrior();

	UCombatComponent* CombatComponent = ActiveWarrior->GetComponentByClass<UCombatComponent>();
	check(CombatComponent);
	OnWarriorEndTurn.AddDynamic(CombatComponent, &UCombatComponent::DecreaseActionSpeed);

	CombatComponent->StartWarriorTurn();
	CombatComponent->OnTurnEnded.AddUniqueDynamic(this, &UBattle::SetReadyForNextTurn);
}

bool UBattle::IsReadyForNextTurn() const
{
	//Check if Player1 is Alive
	const bool bPlayer1Alive = AliveWarriors.ContainsByPredicate([&](const ABC_WarriorBase* Warrior)
	{
		ABC_BattlePlayerController* OwningPlayer = Warrior->GetOwner<ABC_BattlePlayerController>();
		if(Player1 == OwningPlayer)
		{
			return Warrior->IsAlive();
		}
		return false;
	});

	//Check if Player2 is Alive
	const bool bPlayer2Alive = AliveWarriors.ContainsByPredicate([&](const ABC_WarriorBase* Warrior)
	{
		ABC_BattlePlayerController* OwningPlayer = Warrior->GetOwner<ABC_BattlePlayerController>();
		if(Player2 == OwningPlayer)
		{
			return Warrior->IsAlive();
		}
		return false;
	});
	
	return bPlayer1Alive && bPlayer2Alive;
}

void UBattle::SetReadyForNextTurn()
{
	bReadyForNextTurn = true;

	if (IsReadyForNextTurn())
	{
		//Subtract Next Warrior ActionSpeed from each Alive Warrior
		const float SubstructionValue = AliveWarriors[1]->GetActionSpeed();
		OnWarriorEndTurn.Broadcast(SubstructionValue);
		
		StartTurn();
	}
}

TObjectPtr<ABC_WarriorBase> UBattle::GetNextTurnWarrior()
{
	if(AliveWarriors.Num() == 0)
	{
		return nullptr;
	}
	
	AliveWarriors.Sort([](const TObjectPtr<ABC_WarriorBase>& Warrior1, const TObjectPtr<ABC_WarriorBase>& Warrior2)
	{
		return Warrior1->GetActionSpeed() < Warrior2->GetActionSpeed();
	});
	
	return AliveWarriors[0];
}

void UBattle::SpawnWarriors(ABC_BattlePlayerController* PlayerController, TArray<ABattlePosition*> BattlePositions)
{
	const TArray<TSubclassOf<ABC_WarriorBase>>& WarriorClasses = PlayerController->GetPlayerWarriorClasses();

	//validation checking
	checkf(WarriorClasses.Num() > 0 && WarriorClasses.Num() > 4,TEXT("Player [%s] Warrior Classes length is [%n]"), *PlayerController->GetName(),PlayerController->GetPlayerWarriorClasses().Num())
	checkf(BattlePositions.Num() >0 && BattlePositions.Num() < 4,TEXT("BattlePositions[%s].Num[%n] is invalid"), *PlayerController->GetName(), BattlePositions.Num());
	
	for (uint8 i = 0; i < WarriorClasses.Num(); i++)
	{
		ABC_WarriorBase* WarriorToSpawn = GetWorld()->SpawnActorDeferred<ABC_WarriorBase>(WarriorClasses[i], FTransform::Identity, PlayerController);

		UCombatComponent* CombatComponent = WarriorToSpawn->GetComponentByClass<UCombatComponent>();
		OnWarriorEndTurn.AddUniqueDynamic(CombatComponent, &UCombatComponent::DecreaseActionSpeed);
		
		AliveWarriors.Add(WarriorToSpawn);
		
		WarriorToSpawn->FinishSpawning(BattlePositions[i]->GetActorTransform());
	}
}
