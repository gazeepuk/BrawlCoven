// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BC_GameModeBase.h"
#include "BC_BattleGameModeBase.generated.h"

class ABC_PlayerStateBase;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_BattleGameModeBase : public ABC_GameModeBase
{
	GENERATED_BODY()
public:
	ABC_BattleGameModeBase();
	TObjectPtr<ABC_PlayerStateBase> Player1;
	
};
