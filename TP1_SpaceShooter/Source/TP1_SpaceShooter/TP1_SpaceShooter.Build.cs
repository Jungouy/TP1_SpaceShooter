// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP1_SpaceShooter : ModuleRules
{
	public TP1_SpaceShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TP1_SpaceShooter",
			"TP1_SpaceShooter/Variant_Platforming",
			"TP1_SpaceShooter/Variant_Combat",
			"TP1_SpaceShooter/Variant_Combat/AI",
			"TP1_SpaceShooter/Variant_SideScrolling",
			"TP1_SpaceShooter/Variant_SideScrolling/Gameplay",
			"TP1_SpaceShooter/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
