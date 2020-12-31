using UnrealBuildTool;
using System.Collections.Generic;

public class FantasyRPGEditorTarget : TargetRules
{
	public FantasyRPGEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "FantasyRPG" } );
	}
}
