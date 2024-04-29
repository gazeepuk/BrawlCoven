// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Combat/Components/BattleKitComponent.h"
#include "PlayerControllers/BC_PlayerControllerBase.h"
#include "BC_BattlePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnChangedDelegate, bool, NewInTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNextWarriorSetDelegate, const ABC_WarriorBase*, NextWarrior, bool, bPlayerOwns);


class UInputAction;
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
	UPROPERTY(BlueprintAssignable)
	FOnTurnChangedDelegate OnTurnChanged;

	UPROPERTY(BlueprintAssignable)
	FOnNextWarriorSetDelegate OnNextWarriorSet;
	
	UFUNCTION(Server, Reliable)
	void Server_AddWarrior(ABC_WarriorBase* InWarrior);

	UFUNCTION(Server,Reliable)
	void Server_SetActiveWarrior(ABC_WarriorBase* InActiveWarrior);
	
	FORCEINLINE
	const TArray<TObjectPtr<ABC_WarriorBase>>& GetWarriors() const { return Warriors; }
	
	UFUNCTION(Client, Reliable)
	void Client_StartPlayerTurn();
	UFUNCTION(Client, Reliable)
	void Client_EndPlayerTurn();

	bool HasAliveWarriors() const;
	UFUNCTION()
	void OnNextWarriorTurn() const;
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupInputComponent() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle|Components")
	TObjectPtr<UBattleKitComponent> BattleKitComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input|InputAction")
	TObjectPtr<UInputAction> MouseClickInputAction;
	
	void SetIsInTurn(bool NewInTurn);
	bool bInTurn = false;

	UFUNCTION()
	void OnMouseClicked(const FInputActionValue& InputActionValue);
private:
	UPROPERTY(Replicated)
	TArray<TObjectPtr<ABC_WarriorBase>> Warriors;

	UPROPERTY(ReplicatedUsing = OnRep_ActiveWarrior)
	ABC_WarriorBase* ActiveWarrior;

	UFUNCTION()
	void OnRep_ActiveWarrior();
};

