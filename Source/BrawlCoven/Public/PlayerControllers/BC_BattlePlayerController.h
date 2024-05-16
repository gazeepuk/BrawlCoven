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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedWarriorSetDelegate, const ABC_WarriorBase*, SelectedWarrior);

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

	UPROPERTY(BlueprintAssignable)
	FOnSelectedWarriorSetDelegate SelectedWarriorSet;

	UFUNCTION(Server, Reliable)
	void Server_AddPlayerWarrior(ABC_WarriorBase* InWarrior);
	UFUNCTION(Server, Reliable)
	void Server_AddEnemyWarrior(ABC_WarriorBase* InWarrior);

	UFUNCTION(Server,Reliable)
	void Server_SetActiveWarrior(ABC_WarriorBase* InActiveWarrior);
	
	FORCEINLINE
	const TArray<TObjectPtr<ABC_WarriorBase>>& GetWarriors() const { return PlayerWarriors; }
	
	UFUNCTION(Client, Reliable)
	void Client_StartPlayerTurn();
	UFUNCTION(Client, Reliable)
	void Client_EndPlayerTurn();

	bool HasAliveWarriors() const;
	UFUNCTION()
	void OnNextWarriorTurn();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	ABC_WarriorBase* GetActiveWarrior() const {return ActiveWarrior;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ABC_WarriorBase*> GetPlayerWarriors() const {return PlayerWarriors;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ABC_WarriorBase*> GetEnemyWarriors() const {return EnemyWarriors;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABC_WarriorBase* GetSelectedWarrior()const {return SelectedWarrior;}
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

	UFUNCTION(Server,Reliable)
	void Server_SetSelectedWarrior(ABC_WarriorBase* InSelectedWarrior);

private:
	UPROPERTY(Replicated)
	TArray<TObjectPtr<ABC_WarriorBase>> PlayerWarriors;
	UPROPERTY(Replicated)
	TArray<TObjectPtr<ABC_WarriorBase>> EnemyWarriors;

	UPROPERTY(ReplicatedUsing = OnRep_ActiveWarrior)
	ABC_WarriorBase* ActiveWarrior;

	UPROPERTY()
	ABC_WarriorBase* SelectedWarrior;
	
	UFUNCTION()
	void OnRep_ActiveWarrior();

	UFUNCTION(Client, Reliable)
	void Client_OnSelectedWarriorSet();
};

