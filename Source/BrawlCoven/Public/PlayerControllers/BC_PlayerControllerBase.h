 // Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "BC_PlayerControllerBase.generated.h"

 class UBC_AbilitySystemComponent;
 class UBC_InputConfig;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	ABC_PlayerControllerBase();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputContext;

	virtual void SetupInputComponent() override;
private:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UBC_InputConfig> InputConfig;

	TObjectPtr<UBC_AbilitySystemComponent> BCAbilitySystemComponent;
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UBC_AbilitySystemComponent* GetASC();
};
