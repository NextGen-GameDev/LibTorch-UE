// © 2023 Kaya Adrian.

using UnrealBuildTool;


/**
 * Module which implements editor functionality of ATUM
 */
public class AtumEditor : ModuleRules
{
	// ReSharper disable once InconsistentNaming
	/**
	 * Constructor
	 */
	public AtumEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.CPlusPlus;
		PCHUsage = PCHUsageMode.NoPCHs;
		IWYUSupport = IWYUSupport.Full;
		CppStandard = CppStandardVersion.Cpp20;
		
		bUseRTTI = true;
		bUseUnity = false;
		bUsePrecompiled = false;
		bEnableExceptions = true;
		
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Atum",
			"Core",
			"CoreUObject",
			"Json",
			"JsonUtilities" 
		});
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"AssetTools",
			"GraphEditor",
			"Slate",
			"SlateCore",
			"UnrealEd", 
			"DesktopWidgets"
		});
	}
}
