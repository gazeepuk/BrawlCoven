// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattlePosition.generated.h"

class ABC_WarriorBase;
class UArrowComponent;

UCLASS(Blueprintable, BlueprintType)
class BRAWLCOVEN_API ABattlePosition : public AActor
{
	GENERATED_BODY()
	
public:	
	ABattlePosition();

	ABC_WarriorBase* SpawnWarrior(TSubclassOf<ABC_WarriorBase> InWarriorClass, TObjectPtr<AController> InPC) const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UArrowComponent> Arrow;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPrimitiveComponent> Root;
	UPROPERTY(EditAnywhere)
	bool bEnemyPlacement = false;
};
