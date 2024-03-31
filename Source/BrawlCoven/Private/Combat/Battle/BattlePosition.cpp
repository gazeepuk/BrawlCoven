// Ivan Piankouski / GazeePuk


#include "Combat/Battle/BattlePosition.h"

#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Components/ArrowComponent.h"

ABattlePosition::ABattlePosition()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<UPrimitiveComponent>("Root");
	SetRootComponent(Root);

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	const FLinearColor ArrowColor = bEnemyPlacement ? FLinearColor::Green : FLinearColor::Red;
	Arrow->SetArrowColor(ArrowColor);
	Arrow->SetupAttachment(GetRootComponent());
}

void ABattlePosition::BeginPlay()
{
	Super::BeginPlay();
	
}

ABC_WarriorBase* ABattlePosition::SpawnWarrior(TSubclassOf<ABC_WarriorBase> InWarriorClass, TObjectPtr<AController> InPC) const
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	ABC_WarriorBase* WarriorToSpawn = GetWorld()->SpawnActor<ABC_WarriorBase>(InWarriorClass, SpawnParameters);
	WarriorToSpawn->PossessedBy(InPC);
	return WarriorToSpawn;
}


