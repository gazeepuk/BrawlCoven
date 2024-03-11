// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameCardBase.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UGameCardBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void ApplyEffectToTarget(AActor* ActorTarget);

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
