// © 2023 Kaya Adrian.

#pragma once

#include "AssetTypeCategories.h"
#include "Modules/ModuleManager.h"

class FAssetTypeActions_AtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "IAtumEditorModule"

/**
 * Editor ATUM Module interface
 */
class ATUMEDITOR_API IAtumEditorModule : public IModuleInterface
{
protected:
	/**
	 * Category in which ATUM assets can be found within the editor interface
	 */
	EAssetTypeCategories::Type AtumAssetCategoryBit;
	
	/**
	 * Reference to the neural network type asset actions
	 */
	TSharedRef<FAssetTypeActions_AtumNeuralNetwork> AtumNeuralNetworkAssetTypeActions;
	
public:
	/**
	 * Name of this module
	 */
	static const FName ModuleName;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	IAtumEditorModule() noexcept;
	
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
	static FORCEINLINE IAtumEditorModule& GetModule()
	{ return FModuleManager::LoadModuleChecked<IAtumEditorModule>(ModuleName); }
	
	/**
	 * Getter for AtumAssetCategoryBit
	 */
	[[nodiscard]]
	FORCEINLINE EAssetTypeCategories::Type GetAtumAssetCategoryBit() const noexcept { return AtumAssetCategoryBit; }
	
	/**
	 * Getter for AtumNeuralNetworkAssetTypeActions
	 */
	[[nodiscard]]
	FORCEINLINE TSharedRef<const FAssetTypeActions_AtumNeuralNetwork>
	GetAtumNeuralNetworkAssetTypeActions() const noexcept { return AtumNeuralNetworkAssetTypeActions; }
};

#undef LOCTEXT_NAMESPACE
