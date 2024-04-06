// Ivan Piankouski / GazeePuk


#include "Combat/Components/BattleKitComponent.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "GameCards/AbilityCard.h"
#include "GameCards/FieldCard.h"


UBattleKitComponent::UBattleKitComponent()
{
	SetIsReplicated(true);

	PrimaryComponentTick.bCanEverTick = false;
}


void UBattleKitComponent::BeginPlay()
{
	Super::BeginPlay();

	//TODO: Get FBattleKit struct from DB
	const FBattleKit BattleKit =
		FBattleKit
		(
			{ABC_WarriorBase::StaticClass(), ABC_WarriorBase::StaticClass(), ABC_WarriorBase::StaticClass()},
			{UFieldCard::StaticClass(), UFieldCard::StaticClass(), UFieldCard::StaticClass()},
			{UAbilityCard::StaticClass(), UAbilityCard::StaticClass(), UAbilityCard::StaticClass()}
		);

	WarriorClasses = BattleKit.WarriorClasses;

	//Setup enable Warriors
	for (const TSubclassOf<ABC_WarriorBase>& WarriorClass : WarriorClasses)
	{
		//Find prevents duplicate Warriors
		WarriorEnablement.FindOrAdd(WarriorClass, true);
	}

	//Create FieldCards
	for (const TSubclassOf<UFieldCard>& FieldCardClass : BattleKit.FieldCardClasses)
	{
		TObjectPtr<UFieldCard> FieldCard = NewObject<UFieldCard>(this, FieldCardClass);
		FieldCards.Add(FieldCard);
	}

	//Create AbilityCards
	for (const TSubclassOf<UAbilityCard>& AbilityCardClass : BattleKit.AbilityCardClasses)
	{
		TObjectPtr<UAbilityCard> AbilityCard = NewObject<UAbilityCard>(this, AbilityCardClass);
		AbilityCards.Add(AbilityCard);
	}
}
