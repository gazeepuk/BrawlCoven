// Ivan Piankouski / GazeePuk


#include "BC_GameplayTags.h"
#include "GameplayTagsManager.h"

FBC_GameplayTags FBC_GameplayTags::GameplayTags;

void FBC_GameplayTags::InitializeNativeGameplayTags()
{
	//Primary Attributes
	GameplayTags.Attributes_Primary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary..MaxHealth"), "Warrior Max Health");
	GameplayTags.Attributes_Primary_MaxUltimateEnergy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary..MaxUltimateEnergy"), "Warrior Max UltimateEnergy");
	GameplayTags.Attributes_Primary_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Speed"), "Increase doge rate");
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), "Increase Magic dealing damage");
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), "Increase Physical dealing damage");
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), "Increase protection");

	//Secondary Attributes
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), "Decrease taking damage");
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), "Increase armor break damage");
	GameplayTags.Attributes_Secondary_CritDmg = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritDmg"), "Increase Critical Damage");
	GameplayTags.Attributes_Secondary_CritRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritRate"), "Increase Critical Damage Rate");
	
	//Vital Attributes
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), "Warrior Health");
	GameplayTags.Attributes_Vital_UltimateEnergy = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.UltimateEnergy"), "Warrior Health");

	//Elements
	GameplayTags.Elements_Destruction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Destruction"), "Units of this type have high damage, but low survival");
	GameplayTags.Elements_Erosion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Erosion"), "Units of this type specialize on debuffing opponents");
	GameplayTags.Elements_Magnification = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Magnification"), "Units of this type specialize on buffing themselves");
	GameplayTags.Elements_Sustenance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Sustenance"), "Units of this type have high survival, but low damage");

	//InputTags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), "Input Tag for Left Mouse Button");
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), "Input Tag for Right Mouse Button");
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), "Input Tag for 1 key");
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), "Input Tag for 2 key");
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), "Input Tag for 3 key");
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), "Input Tag for 4 key");

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"));

	GameplayTags.Event_Montage_ApplyAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.ApplyDamage"));
	GameplayTags.Event_Montage_SpawnProjectile = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.SpawnProjectile"));
}
