// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProyectoIA_Multi : ModuleRules
{
	public ProyectoIA_Multi(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
			"OnlineSubsystem",
            "OnlineSubsystemUtils",
        });

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ProyectoIA_Multi",
			"ProyectoIA_Multi/Variant_Platforming",
			"ProyectoIA_Multi/Variant_Platforming/Animation",
			"ProyectoIA_Multi/Variant_Combat",
			"ProyectoIA_Multi/Variant_Combat/AI",
			"ProyectoIA_Multi/Variant_Combat/Animation",
			"ProyectoIA_Multi/Variant_Combat/Gameplay",
			"ProyectoIA_Multi/Variant_Combat/Interfaces",
			"ProyectoIA_Multi/Variant_Combat/UI",
			"ProyectoIA_Multi/Variant_SideScrolling",
			"ProyectoIA_Multi/Variant_SideScrolling/AI",
			"ProyectoIA_Multi/Variant_SideScrolling/Gameplay",
			"ProyectoIA_Multi/Variant_SideScrolling/Interfaces",
			"ProyectoIA_Multi/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
