// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "BC_GameplayTags.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WarriorElementDataAsset.generated.h"

class USlateBrushAsset;

USTRUCT(BlueprintType)
struct FWarriorElementInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ElementTag = FBC_GameplayTags::Get().Elements_Destruction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const UTexture2D* Texture = nullptr;
};
/**
 * 
 */
UCLASS(BlueprintType)
class BRAWLCOVEN_API UWarriorElementDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FWarriorElementInfo> WarriorTypeInfos;

	UFUNCTION(BlueprintCallable)
	const UTexture2D* GetWarriorSlateBrushForElement(const FGameplayTag& InWarriorElementTag) const;
};
