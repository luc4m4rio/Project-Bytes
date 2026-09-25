using UnrealBuildTool;

public class ProjectBytesTarget : TargetRules
{
	public ProjectBytesTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ProjectBytes");
	}
}
