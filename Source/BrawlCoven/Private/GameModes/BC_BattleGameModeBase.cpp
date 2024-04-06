// Ivan Piankouski / GazeePuk


#include "GameModes/BC_BattleGameModeBase.h"

#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "GameFramework/GameSession.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/BC_BattlePlayerController.h"
#include "PlayerStates/BC_BattlePlayerState.h"

ABC_BattleGameModeBase::ABC_BattleGameModeBase()
{
	PlayerStateClass = ABC_BattlePlayerState::StaticClass();
	PlayerControllerClass = ABC_BattlePlayerController::StaticClass();
	AbilitySystemComponent = CreateDefaultSubobject<UBC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	AttributeSet = CreateDefaultSubobject<UBC_WarriorAttributeSet>("AttributeSet");
}

void ABC_BattleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	
	check(InitStatsGameplayEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitStatsGameplayEffectClass, 1, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent);
}

FString ABC_BattleGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                              const FString& Options, const FString& Portal)
{
	FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	if(HasAuthority())
	{
		if(Player1 == nullptr)
		{
			ABC_BattlePlayerState* PlayerState1 = NewPlayerController->GetPlayerState<ABC_BattlePlayerState>();
			check(PlayerState1);
			Player1 = PlayerState1; 
		}
		else if (Player2 == nullptr)
		{
			ABC_BattlePlayerState* PlayerState2 = NewPlayerController->GetPlayerState<ABC_BattlePlayerState>();
			check(PlayerState2);
			Player2 = PlayerState2;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Yellow, "Extra player");
			//UGameplayStatics::RemovePlayer(NewPlayerController, true);
		}
	}
	return ErrorMessage;
}
