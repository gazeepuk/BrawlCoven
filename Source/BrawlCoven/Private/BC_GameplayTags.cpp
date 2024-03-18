// Ivan Piankouski / GazeePuk


#include "BC_GameplayTags.h"
#include "GameplayTagsManager.h"

FBC_GameplayTags FBC_GameplayTags::GameplayTags;

void FBC_GameplayTags::InitializeNativeGameplayTags()
{
	//Primary Attributes
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), "Increase Magic dealing attacks");
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), "Increase protection");
	GameplayTags.Attributes_Primary_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Speed"), "Increase doge rate");
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), "Increase Magic dealing attacks");
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), "Increase Health");

	//Secondary Attributes
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), "Decrease taking damage");
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), "Increase armor break damage");
	GameplayTags.Attributes_Secondary_CritDmg = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritDmg"), "Increase Critical Damage");
	GameplayTags.Attributes_Secondary_CritRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritRate"), "Increase Critical Damage Rate");

	//Vital Attributes
	GameplayTags.Attributes_Secondary_CritDmg = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), "Warrior Health");

	//Elements
	GameplayTags.Elements_Destruction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Destruction"));
	GameplayTags.Elements_Erosion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Erosion"));
	GameplayTags.Elements_Magnification = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Magnification"));
	GameplayTags.Elements_Sustenance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Elements.Sustenance"));
}
