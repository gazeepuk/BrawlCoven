// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "BC_InputConfig.generated.h"

USTRUCT(BlueprintType)
struct FBCInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InputActions")
	TArray<FBCInputAction> AbilityInputActions;
};
