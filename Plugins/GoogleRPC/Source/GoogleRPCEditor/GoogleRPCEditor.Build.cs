// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GoogleRPCEditor : ModuleRules
{
	public GoogleRPCEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			});

	}
}
