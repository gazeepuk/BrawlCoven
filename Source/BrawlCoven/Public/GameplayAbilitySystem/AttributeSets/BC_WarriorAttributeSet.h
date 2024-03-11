// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BC_WarriorAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_WarriorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UBC_WarriorAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	// Begin Vital Attributes
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Health, Category = "Vital Stats")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Health)
	// End Vital Attributes


	//Begin Primary Attributes
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Speed, Category = "Primary Stats")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Speed)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Strength, Category = "Primary Stats")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Strength)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Intelligence, Category = "Primary Stats")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Intelligence)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Resilience, Category = "Primary Stats")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Resilience)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Vigor, Category = "Primary Stats")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Vigor)
	// End Primary Attributes

	//Begin Secondary Attributes
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Armor, Category = "Secondary Stats")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Armor)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_ArmorPenetration, Category = "Secondary Stats")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, ArmorPenetration)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_CritRate, Category = "Secondary Stats")
	FGameplayAttributeData CritRate;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, CritRate)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_CritDmg, Category = "Secondary Stats")
	FGameplayAttributeData CritDmg;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, CritDmg)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_MaxHealth, Category = "Secondary Stats")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, MaxHealth)
	//End Secondary Attributes
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_CritRate(const FGameplayAttributeData& OldCritRate) const;
	UFUNCTION()
	void OnRep_CritDmg(const FGameplayAttributeData& OldCritDmg) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
};
