// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BC_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_AssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UBC_AssetManager& Get();
protected:

	virtual void StartInitialLoading() override;
};
