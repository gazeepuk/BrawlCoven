// Ivan Piankouski / GazeePuk


#include "Actors/Pawns/Tests/BC_OnlineTestWarrior.h"
#include "OnlineSubsystem.h"

ABC_OnlineTestWarrior::ABC_OnlineTestWarrior()
{
	PrimaryActorTick.bCanEverTick = false;


	IOnlineSubsystem* OnlineSubsystemInterface = IOnlineSubsystem::Get();

	if (OnlineSubsystemInterface)
	{
		OnlineSessionInterface = OnlineSubsystemInterface->GetSessionInterface();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,15.f, FColor::Blue,FString::Printf(TEXT("Found Subsystem [%s]"), *OnlineSubsystemInterface->GetSubsystemName().ToString()));
		}
	}
}

void ABC_OnlineTestWarrior::BeginPlay()
{
	Super::BeginPlay();
}

void ABC_OnlineTestWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
