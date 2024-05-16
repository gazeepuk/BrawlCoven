// Ivan Piankouski / GazeePuk

#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"


void UBC_WarriorAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, UltimateEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, ActionSpeed, COND_None, REPNOTIFY_Always);

	//Primary
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
	DOREPLIFETIME_CONDITION_NOTIFY(UBC_WarriorAttributeSet, MaxUltimateEnergy, COND_None, REPNOTIFY_Always);
}

void UBC_WarriorAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutProps) const
{
	OutProps.EffectContextHandle = Data.EffectSpec.GetContext();
	OutProps.SourceASC = OutProps.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(OutProps.SourceASC) && OutProps.SourceASC->AbilityActorInfo.IsValid() && OutProps.SourceASC->AbilityActorInfo->AvatarActor.
		IsValid())
	{
		OutProps.SourceAvatarActor = OutProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
		OutProps.SourceController = OutProps.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (OutProps.SourceController == nullptr && OutProps.SourceAvatarActor != nullptr)
		{
			const APawn* SourcePawn = Cast<APawn>(OutProps.SourceAvatarActor);
			if (SourcePawn)
			{
				OutProps.SourceController = SourcePawn->GetController();
			}
		}
		if (OutProps.SourceController)
		{
			OutProps.SourcePawn = Cast<ACharacter>(OutProps.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		OutProps.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		OutProps.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		OutProps.TargetPawn = Cast<APawn>(OutProps.TargetAvatarActor);
		OutProps.TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OutProps.TargetAvatarActor);
	}
}

void UBC_WarriorAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	NewValue = FMath::CeilToInt(NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (NewValue < 0.f)
	{
		NewValue = 0.f;
	}
	
}

void UBC_WarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	Data.EvaluatedData.Magnitude = FMath::CeilToInt(Data.EvaluatedData.Magnitude);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		if(GetHealth() <=0 )
		{
			OnEmptyHealth.Broadcast();
		}
		OnHealthChanged.Broadcast(GetHealth());

	}
	
	if(Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if(LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			if(NewHealth < 0.f)
			{
				SetHealth(0.f);
				OnEmptyHealth.Broadcast();
			}
			else
			{
				SetHealth(NewHealth);
				OnHealthChanged.Broadcast(NewHealth);
			}

			const bool bFatal = NewHealth <= 0.f;
		}
	}

	if(Data.EvaluatedData.Attribute == GetUltimateEnergyAttribute())
	{
		SetUltimateEnergy(FMath::Clamp(GetUltimateEnergy(), 0, GetMaxUltimateEnergy()));
		OnUltimateEnergyChanged.Broadcast(GetUltimateEnergy());
	}
}
#pragma region OnRep_Functions 
void UBC_WarriorAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Health, OldHealth);
}

void UBC_WarriorAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, MaxHealth, OldMaxHealth);
}

void UBC_WarriorAttributeSet::OnRep_UltimateEnergy(const FGameplayAttributeData& OldUltimateEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, MaxHealth, OldUltimateEnergy);
}

void UBC_WarriorAttributeSet::OnRep_MaxUltimateEnergy(const FGameplayAttributeData& OldMaxUltimateEnergy) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, MaxHealth, OldMaxUltimateEnergy);
}

void UBC_WarriorAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, Speed, OldSpeed);
}

void UBC_WarriorAttributeSet::OnRep_ActionSpeed(const FGameplayAttributeData& OldActionSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBC_WarriorAttributeSet, ActionSpeed, OldActionSpeed);
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
#pragma endregion
