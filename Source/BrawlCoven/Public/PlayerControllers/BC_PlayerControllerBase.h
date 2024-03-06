// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BC_PlayerControllerBase.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	ABC_PlayerControllerBase();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputContext;
};
