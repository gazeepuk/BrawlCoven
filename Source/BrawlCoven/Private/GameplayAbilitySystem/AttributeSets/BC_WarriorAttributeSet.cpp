// Ivan Piankouski / GazeePuk

#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UBC_WarriorAttributeSet::UBC_WarriorAttributeSet()
{
	InitHealth(100.f);
	InitSpeed(100.f);
	InitStrength(100.f);
	InitIntelligence(100.f);
}


void UBC_WarriorAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Health, COND_None, REPNOTIFY_Always);

	//Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Resilience, COND_None, REPNOTIFY_Always);

	//Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, CritRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, CritDmg, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UBC_WarriorAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f, GetMaxHealth());
	}
	else if(NewValue < 0.f)
	{
		NewValue = 0.f;
	}
}

void UBC_WarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void UBC_WarriorAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Health, OldHealth);
}

void UBC_WarriorAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, MaxHealth, OldMaxHealth);
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

void UBC_WarriorAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Resilience, OldResilience);
}

void UBC_WarriorAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Armor, OldArmor);
}

void UBC_WarriorAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UBC_WarriorAttributeSet::OnRep_CritRate(const FGameplayAttributeData& OldCritRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, CritRate, OldCritRate);
}

void UBC_WarriorAttributeSet::OnRep_CritDmg(const FGameplayAttributeData& OldCritDmg) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, CritDmg, OldCritDmg);
}

void UBC_WarriorAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Vigor, OldVigor);
}
