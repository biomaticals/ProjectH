// Copyright 2025. Unique Turtle. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectHTarget : TargetRules
{
	public ProjectHTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ProjectH"); 
	}
}
