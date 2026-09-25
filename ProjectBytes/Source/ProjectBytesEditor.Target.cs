using UnrealBuildTool;

public class ProjectBytesEditorTarget : TargetRules
{
	public ProjectBytesEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("ProjectBytes");
	}
}
