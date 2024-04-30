// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ConnectionMenu.generated.h"

class UMultiplayerSessionsSubsystem;
class UButton;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MULTIPLAYERSESSIONS_API UConnectionMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(uint8 InNumberOfPublicConnections = 2, FString InTypeOfMatch = FString(TEXT("FreeForAll")), FString InLobbyPath = "/Game/Maps/LobbyLevel");
protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
private:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> HostButton;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> JoinButton;

	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();

	void MenuTearDown();
	
	TObjectPtr<UMultiplayerSessionsSubsystem> MultiplayerSessionsSubsystem;

	uint8 NumPublicConnections{2};
	FString MatchType{TEXT("FreeForAll")};
	FString PathToLobby{TEXT("")};

	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
	
};
