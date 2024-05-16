// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BrawlCoven : ModuleRules
{
	public BrawlCoven(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "OnlineSubsystemSteam", "OnlineSubsystem"});

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
