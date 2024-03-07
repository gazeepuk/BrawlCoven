// Ivan Piankouski / GazeePuk


#include "GameModes/BC_BattleGameModeBase.h"

#include "PlayerControllers/BC_BattlePlayerController.h"
#include "PlayerStates/BC_BattlePlayerState.h"

ABC_BattleGameModeBase::ABC_BattleGameModeBase()
{
	PlayerStateClass = ABC_BattlePlayerState::StaticClass();
	PlayerControllerClass = ABC_BattlePlayerController::StaticClass();	
}
