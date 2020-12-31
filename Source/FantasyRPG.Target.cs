using UnrealBuildTool;
using System.Collections.Generic;

public class FantasyRPGTarget : TargetRules
{
	public FantasyRPGTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "FantasyRPG" } );
	}
}
