// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BRAWLCOVEN_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual uint8 GetPlayerLevel();
};
