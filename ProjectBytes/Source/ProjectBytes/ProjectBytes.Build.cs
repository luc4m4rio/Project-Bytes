using UnrealBuildTool;

public class ProjectBytes : ModuleRules
{
	public ProjectBytes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"NetCore",
			"DeveloperSettings",
			"Json",
			"JsonUtilities",
			"EnhancedInput",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"HTTP",
		});
	}
}
