// Ivan Piankouski / GazeePuk


#include "PlayerControllers/BC_BattlePlayerController.h"

#include "EnhancedInputComponent.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Combat/Components/BattleKitComponent.h"
#include "Net/UnrealNetwork.h"

ABC_BattlePlayerController::ABC_BattlePlayerController()
{
	bReplicates = true;
	BattleKitComponent = CreateDefaultSubobject<UBattleKitComponent>("BattleKitComponent");
}

void ABC_BattlePlayerController::Server_AddWarrior_Implementation(ABC_WarriorBase* InWarrior)
{
	Warriors.Add(InWarrior);
}

void ABC_BattlePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABC_BattlePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ThisClass, Warriors, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ThisClass, ActiveWarrior, COND_OwnerOnly);
}

void ABC_BattlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputContext);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MouseClickInputAction, ETriggerEvent::Completed, this,
	                                   &ThisClass::OnMouseClicked);
}

void ABC_BattlePlayerController::SetIsInTurn(bool NewInTurn)
{
	bInTurn = NewInTurn;
	OnTurnChanged.Broadcast(bInTurn);
}

void ABC_BattlePlayerController::OnMouseClicked(const FInputActionValue& InputActionValue)
{
	if (!bInTurn)
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

void ABC_BattlePlayerController::Server_SetActiveWarrior_Implementation(ABC_WarriorBase* InActiveWarrior)
{
	ActiveWarrior = InActiveWarrior;
	if(this->HasAuthority())
	{
		OnNextWarriorTurn();
	}
}

bool ABC_BattlePlayerController::HasAliveWarriors() const
{
	return Warriors.Num() > 0 && Warriors.ContainsByPredicate([](const TObjectPtr<ABC_WarriorBase>& Warrior) { return Warrior->IsAlive(); });
}

void ABC_BattlePlayerController::OnNextWarriorTurn() const
{
	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Yellow, *ActiveWarrior->GetName());
	
	OnNextWarriorSet.Broadcast(ActiveWarrior,ActiveWarrior->GetPlayerIndex() == ControllerIndex);
}
void ABC_BattlePlayerController::OnRep_ActiveWarrior()
{
	OnNextWarriorTurn();
}
