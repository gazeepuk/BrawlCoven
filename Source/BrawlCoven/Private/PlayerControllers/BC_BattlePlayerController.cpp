// Ivan Piankouski / GazeePuk


#include "PlayerControllers/BC_BattlePlayerController.h"

#include "Combat/Components/BattleKitComponent.h"

ABC_BattlePlayerController::ABC_BattlePlayerController()
{
	BattleKitComponent = CreateDefaultSubobject<UBattleKitComponent>("BattleKit");
}
