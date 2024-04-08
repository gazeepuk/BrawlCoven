// Ivan Piankouski / GazeePuk


#include "PlayerControllers/BC_BattlePlayerController.h"

#include "Combat/Components/BattleKitComponent.h"

ABC_BattlePlayerController::ABC_BattlePlayerController()
{
	BattleKitComponent = CreateDefaultSubobject<UBattleKitComponent>("BattleKitComponent");
}

void ABC_BattlePlayerController::AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior) const
{
	BattleKitComponent->AddWarrior(InWarrior);
}
