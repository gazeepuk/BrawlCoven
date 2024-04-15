// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BC_WarriorAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEmptyHealthSignature);

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	APawn* SourcePawn = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	APawn* TargetPawn = nullptr;
	
};


/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_WarriorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	FOnEmptyHealthSignature OnEmptyHealth;
	
	// Begin Vital Attributes
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Health, Category = "Vital Stats")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Health)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_UltimateEnergy, Category = "Vital Stats")
	FGameplayAttributeData UltimateEnergy;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, UltimateEnergy)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_ActionSpeed, Category = "Vital Stats")
	FGameplayAttributeData ActionSpeed;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, ActionSpeed)
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
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_MaxUltimateEnergy, Category = "Secondary Stats")
	FGameplayAttributeData MaxUltimateEnergy;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, MaxUltimateEnergy)
	//End Secondary Attributes

	//Begin Meta Attributes
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, IncomingDamage)
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_UltimateEnergy(const FGameplayAttributeData& OldUltimateEnergy) const;
	UFUNCTION()
	void OnRep_MaxUltimateEnergy(const FGameplayAttributeData& OldMaxUltimateEnergy) const;
	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;
	UFUNCTION()
	void OnRep_ActionSpeed(const FGameplayAttributeData& OldActionSpeed) const;
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

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutProps) const;
};
