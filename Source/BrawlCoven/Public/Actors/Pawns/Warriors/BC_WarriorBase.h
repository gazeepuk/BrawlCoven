// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "WarriorDataAsset.h"
#include "GameFramework/Pawn.h"
#include "BC_WarriorBase.generated.h"

class UCombatComponent;
class UWarriorDataAsset;
class UBC_GameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;




UCLASS()
class BRAWLCOVEN_API ABC_WarriorBase : public APawn, public	IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	//GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	template<class T>
	T* GetAttributeSet() const;
	
	ABC_WarriorBase();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	FORCEINLINE
	FName GetWarriorName() const {return WarriorDataAsset->WarriorName;}

	float GetActionSpeed() const;
	bool IsAlive() const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	UPROPERTY()
	TObjectPtr<UCombatComponent> CombatComponent;

	void InitializeDefaultAttributes() const;
	void InitializePrimaryAttributes() const;
	void InitializeSecondaryAttributes() const;

	void AddWarriorAbilities() const;
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	const UWarriorDataAsset* WarriorDataAsset;
	
	void InitAbilityActorInfo();
	void ApplyEffectSpecToSelf(const TSubclassOf<UGameplayEffect>& AttributeClass, float Level = 1) const;
	UFUNCTION()
	void OnDeath();
};
