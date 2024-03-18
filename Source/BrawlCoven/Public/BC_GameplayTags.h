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
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Speed;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Vigor;
	// Attributes Secondary
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_CritDmg;
	FGameplayTag Attributes_Secondary_CritRate;
	// Attributes Vital
	FGameplayTag Attributes_Vital_Health;
	// Elements
	FGameplayTag Elements_Destruction;
	FGameplayTag Elements_Erosion;
	FGameplayTag Elements_Magnification;
	FGameplayTag Elements_Sustenance;
protected:

private:
	static FBC_GameplayTags GameplayTags;
};
