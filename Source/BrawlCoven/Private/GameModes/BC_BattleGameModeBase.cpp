// Ivan Piankouski / GazeePuk


#include "GameModes/BC_BattleGameModeBase.h"

#include "Combat/Battle/Battle.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "GameFramework/GameSession.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "PlayerControllers/BC_BattlePlayerController.h"
#include "PlayerStates/BC_BattlePlayerState.h"

ABC_BattleGameModeBase::ABC_BattleGameModeBase()
{
	PlayerStateClass = ABC_BattlePlayerState::StaticClass();
	PlayerControllerClass = ABC_BattlePlayerController::StaticClass();
	/*AbilitySystemComponent = CreateDefaultSubobject<UBC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UBC_WarriorAttributeSet>("AttributeSet");*/
}

void ABC_BattleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	
	/*check(InitStatsGameplayEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitStatsGameplayEffectClass, 1, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent);*/
}

void ABC_BattleGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABC_BattleGameModeBase, ActiveBattle);
}

void ABC_BattleGameModeBase::OnRep_ActiveBattle()
{
}

FString ABC_BattleGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                              const FString& Options, const FString& Portal)
{
	FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if(HasAuthority())
	{
		if(PlayerState1 == nullptr)
		{
			ABC_BattlePlayerState* PlayerState = NewPlayerController->GetPlayerState<ABC_BattlePlayerState>();
			check(PlayerState);
			PlayerState1 = PlayerState;
			PlayerController1 = CastChecked<ABC_BattlePlayerController>(NewPlayerController);
		}
		else if (PlayerState2 == nullptr)
		{
			ABC_BattlePlayerState* PlayerState = NewPlayerController->GetPlayerState<ABC_BattlePlayerState>();
			check(PlayerState);
			PlayerState2 = PlayerState;
			PlayerController2 = CastChecked<ABC_BattlePlayerController>(NewPlayerController);

			OnPlayersInitialized();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Yellow, "Extra player");
			//UGameplayStatics::RemovePlayer(NewPlayerController, true);
			//UKismetSystemLibrary::QuitGame(GetWorld(), NewPlayerController,EQuitPreference::Quit, false);
		}
	}
	return ErrorMessage;
}
