// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BC_GameModeBase.h"
#include "BC_BattleGameModeBase.generated.h"

class ABC_BattlePlayerState;
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
protected:
	TObjectPtr<ABC_BattlePlayerState> Player1;
	TObjectPtr<ABC_BattlePlayerState> Player2;
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
};
