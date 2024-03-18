// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Combat/CombatInterface.h"
#include "GameFramework/Pawn.h"
#include "BC_WarriorBase.generated.h"

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
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	

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

	UPROPERTY(EditDefaultsOnly, Category = "WarriorInfo", meta = (AllowPrivateAccess))
	FGameplayTag WarriorType;
	UPROPERTY(EditDefaultsOnly, Category = "WarriorInfo", meta = (AllowPrivateAccess))
	FName WarriorName;
	
	UPROPERTY(EditDefaultsOnly, Category = "WarriorInfo", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UBC_GameplayAbility>> StartupAbilities;
	
	void InitAbilityActorInfo();
	void ApplyEffectSpecToSelf(const TSubclassOf<UGameplayEffect>& AttributeClass, float Level = 1) const;
};
