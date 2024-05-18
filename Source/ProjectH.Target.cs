// Copyright 2024. Unique Turtle. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectHTarget : TargetRules
{
	public ProjectHTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("ProjectH"); 
	}
}
