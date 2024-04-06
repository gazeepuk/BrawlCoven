// Ivan Piankouski / GazeePuk


#include "Combat/Components/BattleKitComponent.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "GameCards/AbilityCard.h"
#include "GameCards/FieldCard.h"
#include "PlayerControllers/BC_BattlePlayerController.h"


bool FBattleKit::IsValid() const
{
	return WarriorClasses.Num() > 0 && WarriorClasses.Num() <=3 && FieldCardClasses.Num() > 0 && FieldCardClasses.Num() <=3;
}

UBattleKitComponent::UBattleKitComponent()
{
	SetIsReplicated(true);

	PrimaryComponentTick.bCanEverTick = false;
}


void UBattleKitComponent::BeginPlay()
{
	Super::BeginPlay();

	//TODO: Get FBattleKit struct from DB
	checkf(TemporaryTestKit.IsValid(), TEXT("BattleKit is Invalid"));
	
	WarriorClasses = TemporaryTestKit.WarriorClasses;
	//Setup enable Warriors
	for (const TSubclassOf<ABC_WarriorBase>& WarriorClass : WarriorClasses)
	{
		//Find prevents duplicate Warriors
		WarriorEnablement.FindOrAdd(WarriorClass, true);
	}

	//Create FieldCards
	for (const TSubclassOf<UFieldCard>& FieldCardClass : TemporaryTestKit.FieldCardClasses)
	{
		TObjectPtr<UFieldCard> FieldCard = NewObject<UFieldCard>(this, FieldCardClass);
		FieldCards.Add(FieldCard);
	}

	//Create AbilityCards
	for (const TSubclassOf<UAbilityCard>& AbilityCardClass : TemporaryTestKit.AbilityCardClasses)
	{
		TObjectPtr<UAbilityCard> AbilityCard = NewObject<UAbilityCard>(this, AbilityCardClass);
		AbilityCards.Add(AbilityCard);
	}
}
