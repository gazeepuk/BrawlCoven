// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "GameFramework/Character.h"
#include "BC_OnlineTestWarrior.generated.h"

UCLASS()
class BRAWLCOVEN_API ABC_OnlineTestWarrior : public ACharacter
{
	GENERATED_BODY()

public:
	ABC_OnlineTestWarrior();

protected:
	virtual void BeginPlay() override;

	IOnlineSessionPtr OnlineSessionInterface;
public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
