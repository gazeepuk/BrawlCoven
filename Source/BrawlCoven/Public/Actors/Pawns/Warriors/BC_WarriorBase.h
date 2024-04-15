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
	ABC_WarriorBase();
	
	//GAS
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GAS")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GAS")
	UAttributeSet* GetAttributeSet() const;
	template<class T>
	T* GetAttributeSet() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const UWarriorDataAsset* GetWarriorDataAsset() const {return WarriorDataAsset; };
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	FORCEINLINE
	FName GetWarriorName() const {return WarriorDataAsset->WarriorName;}

	float GetActionSpeed() const;
	bool IsAlive() const;
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCombatComponent> CombatComponent;
	
	void InitializeDefaultAttributes() const;
	
	void InitializePrimaryAttributes() const;
	void InitializeSecondaryAttributes() const;
	void InitializeVitalAttributes() const;

	void AddWarriorAbilities() const;

	void ApplyEffectSpecToSelf(const TSubclassOf<UGameplayEffect>& AttributeClass, float Level = 1) const;
	UFUNCTION()
	void OnDeath();
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	const UWarriorDataAsset* WarriorDataAsset;

	UFUNCTION(Reliable, Server)
	void InitAbilityActorInfo_Server();
	UFUNCTION(Reliable, Client)
	void InitAbilityActorInfo_Client();
	
};
