// Ivan Piankouski / GazeePuk


#include "GameCards/AbilityCard.h"
#include "AbilitySystemComponent.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/BC_BattlePlayerController.h"
#include "PlayerStates/BC_BattlePlayerState.h"

UAbilityCard::UAbilityCard()
{
	if(GetWorld())
	{
		OwningPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ABC_BattlePlayerState>();
	}
}

UAbilitySystemComponent* UAbilityCard::GetAbilitySystemComponent() const
{
	check(OwningPlayer);
	const ABC_BattlePlayerController* PlayerController = CastChecked<ABC_BattlePlayerController>(OwningPlayer->GetPlayerController());
	const ABC_WarriorBase* ActiveWarrior = PlayerController->GetPawn<ABC_WarriorBase>();
	if(!ActiveWarrior)
	{
		return nullptr;
	}
	return ActiveWarrior->GetAbilitySystemComponent();
}

const UAttributeSet* UAbilityCard::GetAttributeSet() const
{
	return GetAbilitySystemComponent()->GetAttributeSet(UBC_WarriorAttributeSet::StaticClass());
}

