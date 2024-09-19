// © 2023 Kaya Adrian.

#pragma once

#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"


#define LOCTEXT_NAMESPACE "IAtumModule"

#if PLATFORM_WINDOWS
/**
 * Structure which deals with releasing the DLL handle pointers
 */
struct FDllDeleter
{
	/**
	 * Unlinks a DLL handle cleanly as soon as the pointer is deleted
	 * 
	 * @param DllHandle Pointer to DLL handle
	 */
	void operator()(uint8* DllHandle) const noexcept;
};
#endif


/**
 * Runtime ATUM Module interface
 */
class ATUM_API IAtumModule : public IModuleInterface
{
protected:
#if PLATFORM_WINDOWS
	/**
	 * Collection of all DLL handles as smart pointers
	 */
	static TArray<TUniquePtr<uint8, FDllDeleter>> DllHandles;
#endif
	
public:
	/**
	 * Name of this module
	 */
	static const FName ModuleName;
	
	/**
	 * Finds where the Content folder of this plugin is located
	 * 
	 * @param AppendedPath Optional path to append after
	 * @return The result of appending another path to the Content folder path
	 */
	static FORCEINLINE FString GetContentDirectory(const FString& AppendedPath = TEXT("")) noexcept
	{ return IPluginManager::Get().FindPlugin(ModuleName.ToString())->GetContentDir() / AppendedPath; }
	
	/**
	 * Finds where the LibTorch library files are located
	 * 
	 * @param OutPath Path to the library folder
	 * @return Was the path found?
	 */
	static bool GetLibraryPath(FString& OutPath) noexcept;
	
	/**
	 * Checks if the module is available
	 * 
	 * @return Is the module loaded in memory?
	 */
	[[nodiscard]]
	static FORCEINLINE bool IsModuleLoaded() noexcept { return FModuleManager::Get().IsModuleLoaded(ModuleName); }
	
	/**
	 * Loads and gets this module by name
	 * 
	 * @return Reference to this module
	 */
	[[nodiscard]]
	static FORCEINLINE IAtumModule& GetModule() { return FModuleManager::LoadModuleChecked<IAtumModule>(ModuleName); }
	
#if PLATFORM_WINDOWS
	/**
	 * Getter for DllHandles
	 */
	[[nodiscard]]
	static FORCEINLINE const TArray<TUniquePtr<uint8, FDllDeleter>>& GetDllHandles() noexcept { return DllHandles; }
#endif
};

#undef LOCTEXT_NAMESPACE
