// Ivan Piankouski / GazeePuk


#include "Combat/Battle/Battle.h"
#include "Combat/Battle/BattlePosition.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Combat/Components/CombatComponent.h"
#include "PlayerControllers/BC_BattlePlayerController.h"


ABattle::ABattle()
{
	bReplicates = true;
}

void ABattle::InitBattle(ABC_BattlePlayerController* PlayerController1, ABC_BattlePlayerController* PlayerController2)
{
	Player1 = PlayerController1;
	Player2 = PlayerController2;
	//Spawning Warriors
	SpawnWarriors_Server(Player1, Player1BattlePositions);
	SpawnWarriors_Server(Player2, Player2BattlePositions);

	if (AliveWarriors.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("NO ALIVE WARRIORS: AliveWarrior.Num() == 0"));
		return;
	}
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

	StartTurn_Client();
}

bool ABattle::SpawnWarriors_Server_Validate(ABC_BattlePlayerController* PlayerController,
                                            const TArray<TSoftObjectPtr<ABattlePosition>>& BattlePositions)
{
	//Validation checking
	const TArray<TSubclassOf<ABC_WarriorBase>>& WarriorClasses = PlayerController->GetPlayerWarriorClasses();

	const bool bBattlePositionsValid = BattlePositions.Num() > 0 && BattlePositions.Num() < 4;
	const bool bWarriorClassesValid = WarriorClasses.Num() > 0 && WarriorClasses.Num() <= BattlePositions.Num();

	return bBattlePositionsValid && bWarriorClassesValid;
}


void ABattle::SpawnWarriors_Server_Implementation(ABC_BattlePlayerController* PlayerController,
                                                  const TArray<TSoftObjectPtr<ABattlePosition>>& BattlePositions)
{
	const TArray<TSubclassOf<ABC_WarriorBase>>& WarriorClasses = PlayerController->GetPlayerWarriorClasses();

	TArray<ABattlePosition*> HardBattlePositions;

	for (TSoftObjectPtr<ABattlePosition> BattlePosition : BattlePositions)
	{
		if (BattlePosition.Get())
		{
			HardBattlePositions.Add(BattlePosition.Get());
		}
	}

	SpawnWarriors_Client(WarriorClasses, HardBattlePositions, PlayerController);
}

void ABattle::SpawnWarriors_Client_Implementation(const TArray<TSubclassOf<ABC_WarriorBase>>& WarriorClasses,
                                                  const TArray<ABattlePosition*>& BattlePositions,
                                                  ABC_BattlePlayerController* OwningPlayerController)
{
	for (uint8 i = 0; i < WarriorClasses.Num(); i++)
	{
		ABC_WarriorBase* WarriorToSpawn = GetWorld()->SpawnActorDeferred<ABC_WarriorBase>(
			WarriorClasses[i], FTransform::Identity, OwningPlayerController);
		FTransform WarriorTransform = BattlePositions[i]->GetActorTransform();
		WarriorTransform.SetScale3D(FVector::One());

		UCombatComponent* CombatComponent = WarriorToSpawn->GetComponentByClass<UCombatComponent>();
		check(CombatComponent);
		OnWarriorEndTurn.AddUniqueDynamic(CombatComponent, &UCombatComponent::DecreaseActionSpeed);
		CombatComponent->OnTurnEnded.AddUniqueDynamic(this, &ABattle::SetReadyForNextTurn);

		WarriorToSpawn->FinishSpawning(WarriorTransform);

		AliveWarriors.Add(WarriorToSpawn);
		OwningPlayerController->AddWarrior(WarriorToSpawn);
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "SpawnWarriors_Client Completed");
	StartTurn_Client();
}

void ABattle::StartTurn_Client_Implementation()
{
	if (!IsReadyForNextTurn())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "No Alive Warriors");
		return;
	}
	bReadyForNextTurn = false;

	const ABC_WarriorBase* ActiveWarrior = GetNextTurnWarrior();

	UCombatComponent* CombatComponent = ActiveWarrior->GetComponentByClass<UCombatComponent>();
	check(CombatComponent);

	CombatComponent->StartWarriorTurn();

}

bool ABattle::IsReadyForNextTurn() const
{
	return Player1->HasAliveWarrior() && Player2->HasAliveWarrior();
}

void ABattle::SetReadyForNextTurn()
{
	bReadyForNextTurn = true;

	if (IsReadyForNextTurn())
	{
		//Subtract Next Warrior ActionSpeed from each Alive Warrior
		const float SubstructionValue = AliveWarriors[1]->GetActionSpeed();
		OnWarriorEndTurn.Broadcast(SubstructionValue);

		StartTurn_Client();
	}
}

TObjectPtr<ABC_WarriorBase> ABattle::GetNextTurnWarrior()
{
	if (AliveWarriors.Num() == 0)
	{
		return nullptr;
	}

	AliveWarriors.Sort([](const TObjectPtr<ABC_WarriorBase>& Warrior1, const TObjectPtr<ABC_WarriorBase>& Warrior2)
	{
		return Warrior1->GetActionSpeed() < Warrior2->GetActionSpeed();
	});

	return AliveWarriors[0];
}
