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
	
	FORCEINLINE
	FName GetWarriorName() const {return WarriorDataAsset->WarriorName;}
	float GetActionSpeed() const;
	bool IsAlive() const;

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerIndex(int32 InPlayerIndex);
	FORCEINLINE
	int32 GetPlayerIndex() const {return PlayerIndex;}

	UFUNCTION(Reliable, Server)
	void Server_InitAbilityActorInfo();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
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

	UPROPERTY(Replicated)
	int32 PlayerIndex;

	UPROPERTY(Replicated)
	bool bActive = false;
	
};