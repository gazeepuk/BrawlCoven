// Ivan Piankouski / GazeePuk


#include "Actors/Pawns/Warriors/BC_WarriorBase.h"

ABC_WarriorBase::ABC_WarriorBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ABC_WarriorBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABC_WarriorBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ABC_WarriorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABC_WarriorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABC_WarriorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

