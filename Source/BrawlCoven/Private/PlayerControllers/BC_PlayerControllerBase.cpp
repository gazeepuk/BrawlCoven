// Ivan Piankouski / GazeePuk

#include "PlayerControllers/BC_PlayerControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "Input/BC_EnhancedInputComponent.h"

ABC_PlayerControllerBase::ABC_PlayerControllerBase()
{
	bReplicates = true;
}

void ABC_PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	check(InputContext);

	//Add InputContext
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(InputContext, 0);

	//Setup behavior
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeGameAndUI);
}

void ABC_PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	UBC_EnhancedInputComponent* BCInputComponent = CastChecked<UBC_EnhancedInputComponent>(InputComponent);

	BCInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed,
	                                     &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ABC_PlayerControllerBase::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, *InputTag.ToString());
}

void ABC_PlayerControllerBase::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(!GetASC())
	{
		return;
	}
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ABC_PlayerControllerBase::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(!GetASC())
	{
		return;
	}
	GetASC()->AbilityInputTagHeld(InputTag);
}

UBC_AbilitySystemComponent* ABC_PlayerControllerBase::GetASC()
{
	if (BCAbilitySystemComponent == nullptr)
	{
		BCAbilitySystemComponent = Cast<UBC_AbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return BCAbilitySystemComponent;
}
