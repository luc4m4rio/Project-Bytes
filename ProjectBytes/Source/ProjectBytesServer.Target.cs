using UnrealBuildTool;

public class ProjectBytesServerTarget : TargetRules
{
	public ProjectBytesServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ProjectBytes");
	}
}
