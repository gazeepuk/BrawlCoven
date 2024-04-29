// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattlePosition.generated.h"

class ABC_WarriorBase;
class UArrowComponent;

UENUM(BlueprintType)
enum class EBattleTeam
{
	None,
	Player_1,
	Player_2
};

UCLASS(Blueprintable, BlueprintType)
class BRAWLCOVEN_API ABattlePosition : public AActor
{
	GENERATED_BODY()
	
public:	
	ABattlePosition();

	FORCEINLINE
	EBattleTeam GetBattleTeam() const{return BattleTeam;}
	
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UArrowComponent> Arrow;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPrimitiveComponent> Root;

	UPROPERTY(EditAnywhere)
	EBattleTeam BattleTeam;

};
