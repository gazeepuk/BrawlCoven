// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	UFUNCTION(Blueprintable)
	void MenuSetup();
protected:
	virtual bool Initialize() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> HostButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> JoinButton;

	UFUNCTION()
	void OnHostButtonPressed();
	UFUNCTION()
	void OnJoinButtonPressed();

private:

	UPROPERTY()
	TObjectPtr<UMultiplayerSessionsSubsystem> MultiplayerSessionsSubsystem;
};
