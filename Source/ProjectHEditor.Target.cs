// Copyright 2024. Unique Turtle. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectHEditorTarget : TargetRules
{
	public ProjectHEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("ProjectH"); 
	}
}
