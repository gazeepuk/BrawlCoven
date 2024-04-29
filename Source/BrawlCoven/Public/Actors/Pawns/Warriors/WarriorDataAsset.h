// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WarriorDataAsset.generated.h"


class UBC_GameplayAbility;
class UGameplayEffect;
class ABC_WarriorBase;
/**
 * 
 */

UCLASS(BlueprintType)
class BRAWLCOVEN_API UWarriorDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABC_WarriorBase> WarriorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WarriorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WarriorDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> SkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag WarriorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBC_GameplayAbility> NormalAttackAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBC_GameplayAbility> SkillAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBC_GameplayAbility> UltimateAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> PrimaryAttributesEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> SecondaryAttributesEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> VitalAttributesEffect;
	
};
