// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * BrawlCoven GameplayTags
 *
 * Singletone containing native GameplayTags
 * 
 */
struct FBC_GameplayTags
{
public:
	static const FBC_GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	// Attributes Primary
	FGameplayTag Attributes_Primary_MaxHealth;
	FGameplayTag Attributes_Primary_MaxUltimateEnergy;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Speed;
	FGameplayTag Attributes_Primary_Strength;
	
	// Attributes Secondary
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_CritDmg;
	FGameplayTag Attributes_Secondary_CritRate;
	// Attributes Vital
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_UltimateEnergy;
	// Elements
	FGameplayTag Elements_Destruction;
	FGameplayTag Elements_Erosion;
	FGameplayTag Elements_Magnification;
	FGameplayTag Elements_Sustenance;
	//Input
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	
	FGameplayTag Damage;

	//Abilities Event Montage
	FGameplayTag Event_Montage_ApplyAttack;
	FGameplayTag Event_Montage_SpawnProjectile;
private:
	static FBC_GameplayTags GameplayTags;
};
