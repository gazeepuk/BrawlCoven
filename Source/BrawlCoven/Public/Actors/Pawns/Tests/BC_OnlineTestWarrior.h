// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "BC_OnlineTestWarrior.generated.h"


UCLASS()
class BRAWLCOVEN_API ABC_OnlineTestWarrior : public ACharacter
{
	GENERATED_BODY()

public:
	ABC_OnlineTestWarrior();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void CreateGameSession();
	UFUNCTION(BlueprintCallable)
	void JoinGameSession();
protected:

	TSharedPtr<IOnlineSession, ESPMode::ThreadSafe> OnlineSessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
private:
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
};
