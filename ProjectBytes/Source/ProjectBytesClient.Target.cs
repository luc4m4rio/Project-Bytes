using UnrealBuildTool;

public class ProjectBytesClientTarget : TargetRules
{
	public ProjectBytesClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ProjectBytes");
	}
}
