// Ivan Piankouski / GazeePuk


#include "UI//ConnectionMenu.h"
#include "Components/Button.h"
#include "Subsystems/MultiplayerSessionsSubsystem.h"

void UConnectionMenu::MenuSetup(uint8 InNumberOfPublicConnections, FString InTypeOfMatch, FString InLobbyPath)
{
	NumPublicConnections = InNumberOfPublicConnections;
	MatchType = InTypeOfMatch;
	PathToLobby = FString::Printf(TEXT("%s?listen"),*InLobbyPath);	
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

	UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
	if(MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionCompleteDelegate.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionCompleteDelegate.AddUObject(this, &ThisClass::OnFindSession);
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionCompleteDelegate.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionCompleteDelegate.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionsSubsystem->MultiplayerOnStartSessionCompleteDelegate.AddDynamic(this, &ThisClass::OnStartSession);
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
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if(JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	
	return true;
}

void UConnectionMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UConnectionMenu::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	if(MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UConnectionMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);
	if(MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSession(10000);
	}
}

void UConnectionMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			const FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

void UConnectionMenu::OnCreateSession(bool bWasSuccessful)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			1	,
			15.f,
			FColor::Yellow,
			FString::Printf(TEXT("Session created successfully [%s]"), bWasSuccessful ? TEXT("true") : TEXT("false")));
	}
	if(bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if(World)
		{
			World->ServerTravel(PathToLobby);
		}
	}
	else
	{
		HostButton->SetIsEnabled(true);
	}
}

void UConnectionMenu::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if(MultiplayerSessionsSubsystem == nullptr || !bWasSuccessful)
	{
		return;
	}
	
	for (const FOnlineSessionSearchResult& SessionResult : SessionResults)
	{
		FString SettingsValue;
		SessionResult.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if(SettingsValue == MatchType)
		{
			MultiplayerSessionsSubsystem->JoinSession(SessionResult);
			return;
		}
	}

	if(!bWasSuccessful || SessionResults.Num() <= 0)
	{
		JoinButton->SetIsEnabled(true);
	}
}

void UConnectionMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if(PlayerController)
			{
				PlayerController->ClientTravel(Address, TRAVEL_Absolute);
			}
		}
	}
	if(Result != EOnJoinSessionCompleteResult::Type::Success)
	{
		JoinButton->SetIsEnabled(true);
	}
}

void UConnectionMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UConnectionMenu::OnStartSession(bool bWasSuccessful)
{
}
