// Ivan Piankouski / GazeePuk

#include "EnhancedInputSubsystems.h"
#include "PlayerControllers/BC_PlayerControllerBase.h"

ABC_PlayerControllerBase::ABC_PlayerControllerBase()
{
	bReplicates = true;
}

void ABC_PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	check(InputContext);

	//Add InputContext
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(InputContext,0);

	//Setup behavior
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeGameAndUI);
}
