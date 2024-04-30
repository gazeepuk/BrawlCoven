// Ivan Piankouski / GazeePuk


#include "GameModes/BC_PlayersLobbyGameMode.h"

#include "GameFramework/GameStateBase.h"


void ABC_PlayersLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
	if (NumOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->GetTimerManager().ClearTimer(ServerTravelTimerHandle);
			World->GetTimerManager().SetTimer(ServerTravelTimerHandle, this, &ThisClass::TravelToBattleLevel,5.f);
		}
	}
}

void ABC_PlayersLobbyGameMode::TravelToBattleLevel()
{
	UWorld* World = GetWorld();
	if (World)
	{
		bUseSeamlessTravel = true;
		World->ServerTravel(FString("/Game/Maps/BattleMap?listen"));
	}
}
