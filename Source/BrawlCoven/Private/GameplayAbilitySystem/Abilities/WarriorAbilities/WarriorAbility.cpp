// Ivan Piankouski / GazeePuk


#include "GameplayAbilitySystem/Abilities/WarriorAbilities/WarriorAbility.h"

#include "Net/UnrealNetwork.h"

void UWarriorAbility::Server_SetTargets_Implementation(const TArray<AActor*>& InTargets)
{
	WarriorTargets.Empty();
	for (AActor* Target : InTargets)
	{
		WarriorTargets.Add(Target);
	} 
}

void UWarriorAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, WarriorTargets);
}
