// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BC_GameModeBase.h"
#include "BC_PlayersLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_PlayersLobbyGameMode : public ABC_GameModeBase
{
	GENERATED_BODY()
private:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	UFUNCTION()
	void TravelToBattleLevel();
	FTimerHandle ServerTravelTimerHandle;
};
