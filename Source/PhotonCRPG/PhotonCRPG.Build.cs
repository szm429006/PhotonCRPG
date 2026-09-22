// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class PhotonCRPG : ModuleRules
{
	public PhotonCRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
			"ArticyRuntime",
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"SlateCore",
			"NavigationSystem",
			"AIModule",
			"Niagara",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});
    }
}
