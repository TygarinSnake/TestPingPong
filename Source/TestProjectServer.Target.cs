using UnrealBuildTool;
using System.Collections.Generic;

public class TestProjectServerTarget : TargetRules
{
    public TestProjectServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("TestProject");
    }
}