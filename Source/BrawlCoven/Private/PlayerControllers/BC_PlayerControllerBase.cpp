// Ivan Piankouski / GazeePuk

#include "PlayerControllers/BC_PlayerControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "Input/BC_EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"

ABC_PlayerControllerBase::ABC_PlayerControllerBase()
{
	bReplicates = true;
}

void ABC_PlayerControllerBase::Server_SetControllerIndex_Implementation(int32 InControllerIndex)
{
	ControllerIndex = InControllerIndex;
}

void ABC_PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	check(InputContext);
	
	//Add InputContext
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}

	//Setup behavior
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeGameAndUI);
	
}

void ABC_PlayerControllerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ThisClass, ControllerIndex, ELifetimeCondition::COND_OwnerOnly);
}


