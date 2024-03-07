// Ivan Piankouski / GazeePuk


#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Net/UnrealNetwork.h"

UBC_WarriorAttributeSet::UBC_WarriorAttributeSet()
{
	InitHealth(100.f);
	InitSpeed(100.f);
	InitStrength(100.f);
	InitIntelligence(100.f);
	InitDefence(100.f);

}

void UBC_WarriorAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Defence, COND_None, REPNOTIFY_Always);
}

void UBC_WarriorAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Health, OldHealth);
}

void UBC_WarriorAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Speed, OldSpeed);
}

void UBC_WarriorAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Strength, OldStrength);
}

void UBC_WarriorAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Intelligence, OldIntelligence);
}

void UBC_WarriorAttributeSet::OnRep_Defence(const FGameplayAttributeData& OldDefence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Defence, OldDefence);
}
