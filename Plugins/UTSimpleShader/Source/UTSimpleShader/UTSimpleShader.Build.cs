// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UTSimpleShader : ModuleRules
{
	public UTSimpleShader(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				EngineDirectory + "/Source/Runtime/Renderer/Private",
			}
			);


		PrivateIncludePaths.AddRange(
			new string[]
			{

			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Renderer",
				"RenderCore",
				"RHI",
				"Projects",
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

			}
			);
	}
}
