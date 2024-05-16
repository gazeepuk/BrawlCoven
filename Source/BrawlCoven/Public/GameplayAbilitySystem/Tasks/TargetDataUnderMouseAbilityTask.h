// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouseAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMousetargetDataSignature, const AActor*, Data);
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UTargetDataUnderMouseAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly))
	static UTargetDataUnderMouseAbilityTask* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMousetargetDataSignature ValidData;
private:
	UFUNCTION(BlueprintCallable)
	virtual void Activate() override;
};
