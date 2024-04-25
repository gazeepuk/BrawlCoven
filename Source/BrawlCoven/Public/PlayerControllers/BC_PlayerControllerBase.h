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
	UFUNCTION(Server, Reliable)
	void Server_SetControllerIndex(int32 InControllerIndex);
	FORCEINLINE
	int32 GetControllerIndex() const {return ControllerIndex;}
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(Replicated)
	int32 ControllerIndex = -1;
};
