// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;
using System.Text.RegularExpressions;

namespace UnrealBuildTool.Rules
{
	public class ApiPlugin : ModuleRules
	{
		public ApiPlugin(TargetInfo target)
		{
			PublicIncludePaths.AddRange(new string[] {"ApiPlugin/Public" });
			PrivateIncludePaths.AddRange(new string[] {"ApiPlugin/Private" });
			PublicDependencyModuleNames.AddRange(new string[] {"Core", "Engine"});
			PrivateDependencyModuleNames.AddRange(new string[] {});
			DynamicallyLoadedModuleNames.AddRange(new string[] {});
		}
	}
}
