// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleKitComponent.generated.h"

class UAbilityCard;
class UFieldCard;
class ABC_WarriorBase;

USTRUCT(Blueprintable)
struct FBattleKitInfo
{
	GENERATED_BODY()
	bool IsValid() const;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABC_WarriorBase>> WarriorClasses;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UFieldCard>> FieldCardClasses;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UAbilityCard>> AbilityCardClasses;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAWLCOVEN_API UBattleKitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBattleKitComponent();


	void AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior);
	FORCEINLINE FBattleKitInfo GetBattleKitInfo() {return TemporaryTestKit;}
	
protected:
	
	virtual void BeginPlay() override;
	
	TArray<TSubclassOf<ABC_WarriorBase>> WarriorClasses;
	TArray<TObjectPtr<ABC_WarriorBase>> Warriors;
	
	TArray<TObjectPtr<UFieldCard>> FieldCards;
	TArray<TObjectPtr<UAbilityCard>> AbilityCards;
private:
	UPROPERTY(EditAnywhere)
	FBattleKitInfo TemporaryTestKit;
};
