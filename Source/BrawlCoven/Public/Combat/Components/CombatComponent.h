// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UBC_WarriorAttributeSet;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnEndedDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BRAWLCOVEN_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();
	void StartWarriorTurn();
	void EndWarriorTurn();
	UFUNCTION()
	void DecreaseActionSpeed(float InSubtractionValue);
	FORCEINLINE float GetActionSpeed() const { return ActionSpeed; }

	FTurnEndedDelegate OnTurnEnded;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBC_WarriorAttributeSet> BC_AttributeSet;

private:
	float InitActionSpeed;
	float ActionSpeed;
};
