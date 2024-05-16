// Ivan Piankouski / GazeePuk


#include "GameModes/BC_BattleGameModeBase.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Combat/Battle/BattlePosition.h"
#include "Combat/Components/CombatComponent.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/BC_BattlePlayerController.h"

void ABC_BattleGameModeBase::SubtractActionSpeedForAllWarriors(const float SubtractingValue)
{
	for (int32 i = 0; i < AliveWarriors.Num(); i++)
	{
		AliveWarriors[i]->GetComponentByClass<UCombatComponent>()->DecreaseActionSpeed(SubtractingValue);
	}
}

void ABC_BattleGameModeBase::EndPlayerTurn()
{
	if (PlayerInTurnIndex < 0)
	{
		EndBattle();
		return;
	}
	PlayerControllers[PlayerInTurnIndex]->Client_EndPlayerTurn();
	if (IsReadyForNextTurn())
	{
		const float SubtractingValue = AliveWarriors[1]->GetActionSpeed();
		SubtractActionSpeedForAllWarriors(SubtractingValue);
		StartTurn();
	}
}

void ABC_BattleGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	const int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();

	ABC_BattlePlayerController* BC_NewPlayer = CastChecked<ABC_BattlePlayerController>(NewPlayer);
	PlayerControllers.Add(BC_NewPlayer);
	BC_NewPlayer->Server_SetControllerIndex(NumOfPlayers - 1);
	if (NumOfPlayers == 2)
	{
		GetWorld()->GetTimerManager().ClearTimer(InitBattleHandle);
		GetWorld()->GetTimerManager().SetTimer(InitBattleHandle, this, &ThisClass::InitBattle, 5.f);
	}
}

void ABC_BattleGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

ABC_WarriorBase* ABC_BattleGameModeBase::GetNextWarrior()
{
	if (AliveWarriors.Num() < 2)
	{
		return nullptr;
	}

	AliveWarriors.Sort([](const TObjectPtr<ABC_WarriorBase>& WarriorX, const TObjectPtr<ABC_WarriorBase>& WarriorY)
	{
		return WarriorX->IsAlive() && WarriorY->IsAlive() && WarriorX->GetActionSpeed() < WarriorY->GetActionSpeed();
	});

	if (PlayerControllers[0]->HasAliveWarriors() && PlayerControllers[1]->HasAliveWarriors())
	{
		return AliveWarriors[0];
	}

	return nullptr;
}

ABC_BattlePlayerController* ABC_BattleGameModeBase::GetPlayerInTurnController(ABC_WarriorBase*& OutNextWarriorInTurn)
{
	ABC_WarriorBase* NextWarrior = GetNextWarrior();
	if (!NextWarrior)
	{
		EndBattle();
		return nullptr;
	}
	PlayerInTurnIndex = NextWarrior->GetPlayerIndex();

	OutNextWarriorInTurn = NextWarrior;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PlayerInTurnIndex);
	if (!PlayerController)
	{
		EndBattle();
		return nullptr;
	}
	ABC_BattlePlayerController* BattlePlayerController = CastChecked<ABC_BattlePlayerController>(PlayerController);

	return BattlePlayerController;
}

ABC_BattlePlayerController* ABC_BattleGameModeBase::GetPlayerOutTurnController() const
{
	const int32 PlayerNotInTurnIndex = PlayerInTurnIndex == 0;
	ABC_BattlePlayerController* PlayerController = CastChecked<ABC_BattlePlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), PlayerNotInTurnIndex));
	return PlayerController;
}

void ABC_BattleGameModeBase::SetupBattlePositions()
{
	TArray<UObject*> BattlePositions;
	GetObjectsOfClass(ABattlePosition::StaticClass(), BattlePositions);
	for (UObject* BattlePositionObject : BattlePositions)
	{
		const ABattlePosition* BattlePosition = Cast<ABattlePosition>(BattlePositionObject);
		BattlePosition->GetBattleTeam() == EBattleTeam::Player_1
			? BattlePositions1.AddUnique(BattlePosition)
			: BattlePositions2.AddUnique(BattlePosition);
	}
	check(BattlePositions1.Num() > 0 && BattlePositions2.Num() > 0);
}

void ABC_BattleGameModeBase::InitBattle()
{
	UE_LOG(LogTemp, Error, TEXT("!!!!PlayersNum : %d"), GameState.Get()->PlayerArray.Num());

	//Get BattlePositions and sort by team type
	SetupBattlePositions();

	PlayerController1 = PlayerControllers[0];
	PlayerController2 = PlayerControllers[1];

	Server_SpawnWarriors(PlayerControllers[0], BattlePositions1);
	Server_SpawnWarriors(PlayerControllers[1], BattlePositions2);
	StartBattle();
}

void ABC_BattleGameModeBase::StartBattle()
{
	ForceNetUpdate();
	if (!IsReadyForNextTurn())
	{
		return;
	}
	ABC_WarriorBase* NextWarrior = GetNextWarrior();
	if (!NextWarrior)
	{
		EndBattle();
		return;
	}
	const float SubtractingValue = NextWarrior->GetActionSpeed();
	SubtractActionSpeedForAllWarriors(SubtractingValue);
	StartTurn();
}

bool ABC_BattleGameModeBase::IsReadyForNextTurn()
{
	ForceNetUpdate();
	return PlayerController1->HasAliveWarriors() && PlayerController2->HasAliveWarriors();
}

void ABC_BattleGameModeBase::EndBattle()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Battle is ended");
}

void ABC_BattleGameModeBase::StartTurn()
{
	ABC_WarriorBase* OutNextWarriorInTurn;
	ABC_BattlePlayerController* PlayerInTurn = GetPlayerInTurnController(OutNextWarriorInTurn);
	if (!PlayerInTurn || !OutNextWarriorInTurn)
	{
		EndBattle();
		return;
	}
	PlayerControllers[0]->Server_SetActiveWarrior(OutNextWarriorInTurn);
	PlayerControllers[1]->Server_SetActiveWarrior(OutNextWarriorInTurn);
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
		const uint32 EnemyIndex = PlayerIndex == 0;

		WarriorToSpawn->Server_SetPlayerIndex(PlayerIndex);

		InBattlePlayerController->Server_AddPlayerWarrior(WarriorToSpawn);
		PlayerControllers[EnemyIndex]->Server_AddEnemyWarrior(WarriorToSpawn);

		AliveWarriors.Add(WarriorToSpawn);
		NetMulticast_SpawnWarriors(InBattlePositions[i].Get()->GetActorTransform(), WarriorToSpawn);
	}
}


void ABC_BattleGameModeBase::NetMulticast_SpawnWarriors_Implementation(
	const FTransform& InWarriorTransform, ABC_WarriorBase*
	InWarriorToSpawn)
{
	InWarriorToSpawn->FinishSpawning(InWarriorTransform);
	InWarriorToSpawn->SetActorScale3D(FVector::One());
	InWarriorToSpawn->Server_InitAbilityActorInfo();
}
