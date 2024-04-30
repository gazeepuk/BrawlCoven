// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UBC_AbilitySystemComponent;
class ABC_WarriorBase;
class UGameplayEffect;
class UBC_WarriorAttributeSet;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnEndedDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BRAWLCOVEN_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();
	void StartWarriorTurn();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_EndWarriorTurn() const;
	UFUNCTION()
	void DecreaseActionSpeed(float InSubtractionValue);
	UFUNCTION()
	void SetDefaultActionSpeed() const;
	void SetProperties(UBC_AbilitySystemComponent* InASC, UBC_WarriorAttributeSet* InAS, ABC_WarriorBase* InWarriorOwner);
	FTurnEndedDelegate OnTurnEnded;

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBC_WarriorAttributeSet> BC_AttributeSet;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBC_AbilitySystemComponent> BC_AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABC_WarriorBase> WarriorOwner;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> SetActionSpeedAttributeEffectClass;
};
