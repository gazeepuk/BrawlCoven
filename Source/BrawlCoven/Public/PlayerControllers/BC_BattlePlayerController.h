// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/BC_PlayerControllerBase.h"
#include "BC_BattlePlayerController.generated.h"

class UBattleKitComponent;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_BattlePlayerController : public ABC_PlayerControllerBase
{
	GENERATED_BODY()
public:
	ABC_BattlePlayerController();
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBattleKitComponent> BattleKitComponent;

};
