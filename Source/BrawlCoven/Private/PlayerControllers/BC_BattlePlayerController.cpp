// Ivan Piankouski / GazeePuk


#include "PlayerControllers/BC_BattlePlayerController.h"

#include "EnhancedInputComponent.h"
#include "Combat/Components/BattleKitComponent.h"

ABC_BattlePlayerController::ABC_BattlePlayerController()
{
	BattleKitComponent = CreateDefaultSubobject<UBattleKitComponent>("BattleKitComponent");
}

void ABC_BattlePlayerController::AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior) const
{
	BattleKitComponent->AddWarrior(InWarrior);
}

void ABC_BattlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	OnTurnChanged.Broadcast(bInTurn);
}

void ABC_BattlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputContext);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MouseClickInputAction, ETriggerEvent::Completed, this, &ThisClass::OnMouseClicked);
}

void ABC_BattlePlayerController::SetIsInTurn(bool NewInTurn)
{
	bInTurn = NewInTurn;
	OnTurnChanged.Broadcast(bInTurn);
}

void ABC_BattlePlayerController::OnMouseClicked(const FInputActionValue& InputActionValue)
{
	if(!bInTurn)
	{
		return;
	}
}

void ABC_BattlePlayerController::Client_EndPlayerTurn_Implementation()
{
	SetIsInTurn(false);
	
}

void ABC_BattlePlayerController::Client_StartPlayerTurn_Implementation()
{
	SetIsInTurn(true);	
}
