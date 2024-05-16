// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySystem/Abilities/BC_GameplayAbility.h"
#include "WarriorAbility.generated.h"

class ABC_WarriorBase;
/**
 * 
 */
UCLASS(BlueprintType)
class BRAWLCOVEN_API UWarriorAbility : public UBC_GameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetTargets(const TArray<AActor*>& InTargets);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	UPROPERTY(Replicated)
	TArray<AActor*> WarriorTargets;
};
