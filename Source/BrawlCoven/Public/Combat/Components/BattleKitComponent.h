// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleKitComponent.generated.h"

class UAbilityCard;
class UFieldCard;
class ABC_WarriorBase;

USTRUCT()
struct FBattleKit
{
	GENERATED_BODY()
	
	TArray<TSubclassOf<ABC_WarriorBase>> WarriorClasses;
	TArray<TSubclassOf<UFieldCard>> FieldCardClasses;
	TArray<TSubclassOf<UAbilityCard>> AbilityCardClasses;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAWLCOVEN_API UBattleKitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBattleKitComponent();

protected:
	virtual void BeginPlay() override;
private:
	TMap<TSubclassOf<ABC_WarriorBase>, bool> WarriorEnablement;
	
	TArray<TSubclassOf<ABC_WarriorBase>> WarriorClasses;
	TArray<TObjectPtr<UFieldCard>> FieldCards;
	TArray<TObjectPtr<UAbilityCard>> AbilityCards;
};
