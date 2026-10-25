// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WARFRONT : ModuleRules
{
	public WARFRONT(ReadOnlyTargetRules Target) : base(Target)
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
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"WARFRONT",
			"WARFRONT/Variant_Platforming",
			"WARFRONT/Variant_Platforming/Animation",
			"WARFRONT/Variant_Combat",
			"WARFRONT/Variant_Combat/AI",
			"WARFRONT/Variant_Combat/Animation",
			"WARFRONT/Variant_Combat/Gameplay",
			"WARFRONT/Variant_Combat/Interfaces",
			"WARFRONT/Variant_Combat/UI",
			"WARFRONT/Variant_SideScrolling",
			"WARFRONT/Variant_SideScrolling/AI",
			"WARFRONT/Variant_SideScrolling/Gameplay",
			"WARFRONT/Variant_SideScrolling/Interfaces",
			"WARFRONT/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
