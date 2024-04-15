// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Combat/Components/BattleKitComponent.h"
#include "PlayerControllers/BC_PlayerControllerBase.h"
#include "BC_BattlePlayerController.generated.h"

class ABC_WarriorBase;
class UBattleKitComponent;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_BattlePlayerController : public ABC_PlayerControllerBase
{
	GENERATED_BODY()

public:
	ABC_BattlePlayerController();

	TArray<TSubclassOf<ABC_WarriorBase>> GetPlayerWarriorClasses() const { return BattleKitComponent->GetBattleKitInfo().WarriorClasses; }

	bool HasAliveWarrior() const { return BattleKitComponent->HasAliveWarrior(); }
	void AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle|Components")
	TObjectPtr<UBattleKitComponent> BattleKitComponent;
};
