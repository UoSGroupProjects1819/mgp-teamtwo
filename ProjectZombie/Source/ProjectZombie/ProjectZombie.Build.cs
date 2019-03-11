// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjectZombie : ModuleRules
{
	public ProjectZombie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "AIModule",
            "GameplayTasks",
            "UMG"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore"
        });
	}
}
