// Ivan Piankouski / GazeePuk


#include "BC_AssetManager.h"

#include "BC_GameplayTags.h"

UBC_AssetManager& UBC_AssetManager::Get()
{
	check(GEngine);
	
	UBC_AssetManager* BC_AssetManager = Cast<UBC_AssetManager>(GEngine->AssetManager);
	check(BC_AssetManager)
	return *BC_AssetManager;
}

void UBC_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FBC_GameplayTags::InitializeNativeGameplayTags();
}
