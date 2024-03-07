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

	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Health, Category = "Warrior Stats")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Speed, Category = "Warrior Stats")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Speed)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Strength, Category = "Warrior Stats")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Strength)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Intelligence, Category = "Warrior Stats")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Intelligence)
	UPROPERTY(BlueprintReadOnly, Replicated = OnRep_Defence, Category = "Warrior Stats")
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UBC_WarriorAttributeSet, Defence)
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Defence(const FGameplayAttributeData& OldDefence) const;
	
};
