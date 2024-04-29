// Ivan Piankouski / GazeePuk


#include "Combat/Battle/BattlePosition.h"

#include "Components/ArrowComponent.h"

ABattlePosition::ABattlePosition()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<UPrimitiveComponent>("Root");
	SetRootComponent(Root);

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	const FLinearColor ArrowColor = BattleTeam == EBattleTeam::Player_1 ? FLinearColor::Green : FLinearColor::Red;
	Arrow->SetArrowColor(ArrowColor);
	Arrow->SetupAttachment(GetRootComponent());
}

