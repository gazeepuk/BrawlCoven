// Ivan Piankouski / GazeePuk


#include "Combat/Components/BattleKitComponent.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "GameCards/AbilityCard.h"


bool FBattleKitInfo::IsValid() const
{
	return WarriorClasses.Num() > 0 && WarriorClasses.Num() <=3 && AbilityCardClasses.Num() <=30;
}

UBattleKitComponent::UBattleKitComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	//SetIsReplicated(true);
}


void UBattleKitComponent::AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior)
{
	Warriors.AddUnique(InWarrior);
}

bool UBattleKitComponent::HasAliveWarrior() const
{

	return Warriors.ContainsByPredicate([](const TObjectPtr<ABC_WarriorBase>& InWarrior)
	{
		return InWarrior->IsAlive();
	});

}

void UBattleKitComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->HasAuthority())
	{
		return;
	}
	//TODO: Get FBattleKit struct from DB
	const FString OwnerName = GetOwner()->GetName() + (GetOwner()->HasAuthority() ? " Server" : " Client");

	checkf(TemporaryTestKit.IsValid(), TEXT("BattleKit is Invalid"));
	
	WarriorClasses = TemporaryTestKit.WarriorClasses;

	//Create AbilityCards
	for (const TSubclassOf<UAbilityCard>& AbilityCardClass : TemporaryTestKit.AbilityCardClasses)
	{
		TObjectPtr<UAbilityCard> AbilityCard = NewObject<UAbilityCard>(this, AbilityCardClass);
		AbilityCards.Add(AbilityCard);
	}
}
