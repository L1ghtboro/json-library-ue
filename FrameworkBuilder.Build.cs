// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrameworkBuilder : ModuleRules
{
	public FrameworkBuilder(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Json", "JsonUtilities", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
