// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Combat/Components/BattleKitComponent.h"
#include "PlayerControllers/BC_PlayerControllerBase.h"
#include "BC_BattlePlayerController.generated.h"

class UInputAction;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnChangedDelegate, bool, NewInTurn);

class ABC_WarriorBase;
class UBattleKitComponent;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API ABC_BattlePlayerController : public ABC_PlayerControllerBase
{
	GENERATED_BODY()

public:
	ABC_BattlePlayerController();

	TArray<TSubclassOf<ABC_WarriorBase>> GetPlayerWarriorClasses() const { return BattleKitComponent->GetBattleKitInfo().WarriorClasses; }

	void AddWarrior(const TObjectPtr<ABC_WarriorBase>& InWarrior) const;

	UFUNCTION(Client, Reliable)
	void Client_StartPlayerTurn();
	UFUNCTION(Client, Reliable)
	void Client_EndPlayerTurn();

	UPROPERTY(BlueprintAssignable)
	FOnTurnChangedDelegate OnTurnChanged;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle|Components")
	TObjectPtr<UBattleKitComponent> BattleKitComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction")
	TObjectPtr<UInputAction> MouseClickInputAction;
	
	
	void SetIsInTurn(bool NewInTurn);
	bool bInTurn = false;

	UFUNCTION()
	void OnMouseClicked(const FInputActionValue& InputActionValue);

};
