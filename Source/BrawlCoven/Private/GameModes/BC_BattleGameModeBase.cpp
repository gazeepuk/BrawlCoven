// Ivan Piankouski / GazeePuk


#include "GameModes/BC_BattleGameModeBase.h"

#include "Combat/Battle/Battle.h"
#include "Combat/Battle/BattlePosition.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/BC_BattlePlayerController.h"


void ABC_BattleGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	const int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
	ABC_BattlePlayerController* BC_NewPlayer = CastChecked<ABC_BattlePlayerController>(NewPlayer);
	BC_NewPlayer->Server_SetControllerIndex(NumOfPlayers - 1);
	PlayerControllers.Add(BC_NewPlayer);


	if (NumOfPlayers == 2)
	{
		GetWorld()->GetTimerManager().ClearTimer(InitBattleHandle);
		GetWorld()->GetTimerManager().SetTimer(InitBattleHandle, this, &ThisClass::InitBattle, 5.f);
	}
}

ABC_WarriorBase* ABC_BattleGameModeBase::GetNextWarrior()
{
	if(AliveWarriors.Num() < 2)
	{
		return nullptr;
	}
	
	AliveWarriors.Sort([](const TObjectPtr<ABC_WarriorBase>& WarriorX, const TObjectPtr<ABC_WarriorBase>& WarriorY)
	{
		return WarriorX->IsAlive() && WarriorY->IsAlive() && WarriorX->GetActionSpeed() < WarriorY->GetActionSpeed();
	});

	if(/*PlayerControllers[0]->HasAliveWarrior() && PlayerControllers[1]->HasAliveWarrior()*/ true)
	{
		return AliveWarriors[0];
	}
	
	return nullptr;
}

ABC_BattlePlayerController* ABC_BattleGameModeBase::GetPlayerInTurnController()
{
	const ABC_WarriorBase* NextWarrior = GetNextWarrior();
	check(NextWarrior)
	PlayerInTurnIndex = NextWarrior->GetPlayerIndex();

	ABC_BattlePlayerController* PlayerController = CastChecked<ABC_BattlePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), PlayerInTurnIndex));
	return PlayerController;
}

ABC_BattlePlayerController* ABC_BattleGameModeBase::GetPlayerOutTurnController() const
{
	const int32 PlayerNotInTurnIndex = PlayerInTurnIndex == 0;
	ABC_BattlePlayerController* PlayerController = CastChecked<ABC_BattlePlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), PlayerNotInTurnIndex));
	return PlayerController;
}

void ABC_BattleGameModeBase::InitBattle()
{
	Server_SpawnWarriors(PlayerControllers[0], BattlePositions1);
	Server_SpawnWarriors(PlayerControllers[1], BattlePositions2);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
	                                 FString::FromInt(PlayerControllers[0]->GetControllerIndex()));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
	                                 FString::FromInt(PlayerControllers[1]->GetControllerIndex()));
	StartBattle();
}

void ABC_BattleGameModeBase::StartBattle()
{
	ABC_BattlePlayerController* PlayerInTurn = GetPlayerInTurnController();
	
	PlayerInTurn->Client_StartPlayerTurn();
}

bool ABC_BattleGameModeBase::Server_SpawnWarriors_Validate(ABC_BattlePlayerController* InBattlePlayerController,
                                                           const TArray<TSoftObjectPtr<ABattlePosition>>&
                                                           InBattlePositions)
{
	if (!InBattlePlayerController)
	{
		return false;
	}
	UBattleKitComponent* BattleKitComponent = InBattlePlayerController->GetComponentByClass<UBattleKitComponent>();
	if (!BattleKitComponent)
	{
		return false;
	}
	const FBattleKitInfo BattleKitInfo = BattleKitComponent->GetBattleKitInfo();
	if (!BattleKitInfo.IsValid())
	{
		return false;
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}

	return true;
}

void ABC_BattleGameModeBase::Server_SpawnWarriors_Implementation(ABC_BattlePlayerController* InBattlePlayerController,
                                                                 const TArray<TSoftObjectPtr<ABattlePosition>>
                                                                 & InBattlePositions)
{
	const FBattleKitInfo BattleKitInfo = InBattlePlayerController->GetComponentByClass<UBattleKitComponent>()->
	                                                               GetBattleKitInfo();
	UWorld* World = GetWorld();
	for (int32 i = 0; i < BattleKitInfo.WarriorClasses.Num(); i++)
	{
		ABC_WarriorBase* WarriorToSpawn = World->SpawnActorDeferred<ABC_WarriorBase>(
			BattleKitInfo.WarriorClasses[i], FTransform::Identity, InBattlePlayerController);
		const uint32 PlayerIndex = InBattlePlayerController->GetControllerIndex();
		WarriorToSpawn->Server_SetPlayerIndex(PlayerIndex);
		WarriorToSpawn->Server_InitAbilityActorInfo();
		AliveWarriors.Add(WarriorToSpawn);
		NetMulticast_SpawnWarriors(InBattlePositions[i].Get()->GetActorTransform(), WarriorToSpawn);
	}
}


void ABC_BattleGameModeBase::NetMulticast_SpawnWarriors_Implementation(
	const FTransform& InWarriorTransform, ABC_WarriorBase*
	InWarriorToSpawn)
{
	InWarriorToSpawn->FinishSpawning(InWarriorTransform);
}
