// Ivan Piankouski / GazeePuk


#include "Combat/Components/BattleKitComponent.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "GameCards/AbilityCard.h"
#include "GameCards/FieldCard.h"


bool FBattleKit::IsValid() const
{
	return WarriorClasses.Num() > 0 && WarriorClasses.Num() <=3 && FieldCardClasses.Num() > 0 && FieldCardClasses.Num() <=3;
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

void UBattleKitComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->HasAuthority())
	{
		return;
	}
	//TODO: Get FBattleKit struct from DB
	const FString OwnerName = GetOwner()->GetName() + (GetOwner()->HasAuthority() ? " Server" : " Client");
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red, OwnerName);
	checkf(TemporaryTestKit.IsValid(), TEXT("BattleKit is Invalid"));
	
	WarriorClasses = TemporaryTestKit.WarriorClasses;
	
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
