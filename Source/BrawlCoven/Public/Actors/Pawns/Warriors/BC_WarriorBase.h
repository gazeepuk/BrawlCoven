// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "WarriorDataAsset.h"
#include "GameFramework/Pawn.h"
#include "GameplayAbilitySystem/Abilities/BC_GameplayAbility.h"
#include "GameplayAbilitySystem/Abilities/WarriorAbilities/WarriorAbility.h"
#include "BC_WarriorBase.generated.h"


class UBC_WarriorCardWidgetController;
class UWidgetComponent;
class UCombatComponent;
class UWarriorDataAsset;
class UBC_GameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;


UCLASS()
class BRAWLCOVEN_API ABC_WarriorBase : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABC_WarriorBase();

	//GAS
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GAS")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GAS")
	UAttributeSet* GetAttributeSet() const;
	template <class T>
	T* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const UWarriorDataAsset* GetWarriorDataAsset() const { return WarriorDataAsset; };

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities")
	UBC_GameplayAbility* GetNormalAttackAbility() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities")
	UBC_GameplayAbility* GetSkillAbility() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities")
	UBC_GameplayAbility* GetUltimateAbility() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE
	FName GetWarriorName() const { return WarriorDataAsset->WarriorName; }

	float GetActionSpeed() const;
	bool IsAlive() const;

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerIndex(int32 InPlayerIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE
	int32 GetPlayerIndex() const { return PlayerIndex; }

	UFUNCTION(Reliable, Server)
	void Server_InitAbilityActorInfo();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE
	void SetCanSelect(bool NewCanSelect) { bCanSelect = NewCanSelect; }

	UPROPERTY(BlueprintReadWrite)
	UBC_GameplayAbility* SelectedGameplayAbility;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_UseWarriorAbility(UWarriorAbility* AbilityToUse, const TArray<AActor*>& Targets);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCombatComponent> CombatComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> CardWidgetComponent;

	TObjectPtr<UBC_WarriorCardWidgetController> WarriorCardWidgetController;

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

	bool bCanSelect = false;
};
