using UnrealBuildTool;
using System.Collections.Generic;

public class TestProjectClientTarget : TargetRules
{
    public TestProjectClientTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Client;
        DefaultBuildSettings = BuildSettingsVersion.V2; 
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("TestProject"); 
    }
}