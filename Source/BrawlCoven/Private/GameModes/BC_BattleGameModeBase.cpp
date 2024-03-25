// Ivan Piankouski / GazeePuk


#include "GameModes/BC_BattleGameModeBase.h"

#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/BC_BattlePlayerController.h"
#include "PlayerStates/BC_BattlePlayerState.h"

ABC_BattleGameModeBase::ABC_BattleGameModeBase()
{
	PlayerStateClass = ABC_BattlePlayerState::StaticClass();
	PlayerControllerClass = ABC_BattlePlayerController::StaticClass();	
}

FString ABC_BattleGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
	const FString& Options, const FString& Portal)
{
	FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if(HasAuthority())
	{
		if(Player1 == nullptr)
		{
			ABC_BattlePlayerState* PlayerState1 = NewPlayerController->GetPlayerState<ABC_BattlePlayerState>();
			check(PlayerState1);
			Player1 = PlayerState1; 
		}
		else if (Player2 == nullptr)
		{
			ABC_BattlePlayerState* PlayerState2 = NewPlayerController->GetPlayerState<ABC_BattlePlayerState>();
			check(PlayerState2);
			Player2 = PlayerState2;
		}
		else
		{
			//UGameplayStatics::RemovePlayer(NewPlayerController, true);
		}
	}
	return ErrorMessage;
}
