// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "WarriorDataAsset.h"
#include "Combat/CombatInterface.h"
#include "GameFramework/Pawn.h"
#include "BC_WarriorBase.generated.h"

class UCombatComponent;
class UWarriorDataAsset;
class UBC_GameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;




UCLASS(Abstract)
class BRAWLCOVEN_API ABC_WarriorBase : public APawn, public	IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

	ABC_WarriorBase();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	virtual uint8 GetPlayerLevel() override;

	FORCEINLINE
	FName GetWarriorName() const {return WarriorDataAsset->WarriorName;}

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	UPROPERTY()
	TObjectPtr<UCombatComponent> CombatComponent;

	UPROPERTY(EditDefaultsOnly, Category = "WarriorInfo")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(EditDefaultsOnly, Category = "WarriorInfo")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	void InitializeDefaultAttributes() const;
	void InitializePrimaryAttributes() const;
	void InitializeSecondaryAttributes() const;

	void AddWarriorAbilities();
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWarriorDataAsset> WarriorDataAsset;
	
	void InitAbilityActorInfo();
	void ApplyEffectSpecToSelf(const TSubclassOf<UGameplayEffect>& AttributeClass, float Level = 1) const;
};
