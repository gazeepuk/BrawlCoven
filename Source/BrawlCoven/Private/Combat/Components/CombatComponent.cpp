// Ivan Piankouski / GazeePuk


#include "Combat/Components/CombatComponent.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::StartWarriorTurn()
{
}

void UCombatComponent::EndWarriorTurn()
{
}

void UCombatComponent::BeginBattle()
{
	
}
