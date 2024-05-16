// Ivan Piankouski / GazeePuk


#include "GameplayAbilitySystem/Tasks/TargetDataUnderMouseAbilityTask.h"

#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Kismet/GameplayStatics.h"

UTargetDataUnderMouseAbilityTask* UTargetDataUnderMouseAbilityTask::CreateTargetDataUnderMouse(
	UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouseAbilityTask* MyObj = NewAbilityTask<UTargetDataUnderMouseAbilityTask>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouseAbilityTask::Activate()
{
	ABC_WarriorBase* Warrior = Cast<ABC_WarriorBase>(Ability->GetCurrentActorInfo()->OwnerActor.Get());
	if(Warrior)
	{
		const int32 ControllerIndex = Warrior->GetPlayerIndex();
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), ControllerIndex);
		if(PC)
		{
			FHitResult HitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
			ValidData.Broadcast(HitResult.GetActor());
		}
	}
}
