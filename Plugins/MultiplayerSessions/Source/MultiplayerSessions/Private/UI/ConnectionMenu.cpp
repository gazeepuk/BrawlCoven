// Ivan Piankouski / GazeePuk


#include "UI/ConnectionMenu.h"
#include "Components/Button.h"
#include "MultiplayerSessions/Public/Subsystems/MultiplayerSessionsSubsystem.h"

void UConnectionMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	const UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

bool UConnectionMenu::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}
	if(HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::OnHostButtonPressed);
	}
	if(JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::OnJoinButtonPressed);
	}
	
	return true;
}

void UConnectionMenu::OnHostButtonPressed()
{
	if(MultiplayerSessionsSubsystem)
	{
		
	}
}

void UConnectionMenu::OnJoinButtonPressed()
{
}
