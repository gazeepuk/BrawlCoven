// Ivan Piankouski / GazeePuk


#include "PlayerStates/BC_BattlePlayerState.h"
#include "Combat/Components/BattleKitComponent.h"


ABC_BattlePlayerState::ABC_BattlePlayerState()
{
	bReplicates = true;
	NetUpdateFrequency = 100.f;
	BattleKitComponent = CreateDefaultSubobject<UBattleKitComponent>("BattleKitComponent");
}

void ABC_BattlePlayerState::AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior) const
{
	BattleKitComponent->AddWarrior(InWarrior);
}
