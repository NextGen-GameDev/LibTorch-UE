// © 2023 Kaya Adrian.

#pragma once

#include "AssetTypeActions_Base.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions_AtumNeuralNetwork"

/**
 * Class that determines how the asset should behave in the editor
 */
class ATUMEDITOR_API FAssetTypeActions_AtumNeuralNetwork : public FAssetTypeActions_Base
{
public:
	/**
	 * Gets which class is supported for these asset actions
	 * 
	 * @return The asset's class
	 */
	[[nodiscard]]
	virtual UClass* GetSupportedClass() const override;
	
	/**
	 * Gets the name of the asset
	 * 
	 * @return Localisable asset name
	 */
	[[nodiscard]]
	virtual FText GetName() const override;
	
	/**
	 * Gets the asset's type colour
	 * 
	 * @return Assigned asset colour
	 */
	[[nodiscard]]
	virtual FColor GetTypeColor() const override;
	
	/**
	 * Gets the categories in which the asset can be found
	 * 
	 * @return Asset categories as a number
	 */
	[[nodiscard]]
	virtual uint32 GetCategories() override;
	
	/**
	 * Specifies how to open the asset editor
	 * 
	 * @param InObjects Neural networks for which the editor should open
	 * @param EditWithinLevelEditor Host of the editor window
	 */
	virtual void OpenAssetEditor(
		const TArray<UObject*>& InObjects,
		TSharedPtr<IToolkitHost> EditWithinLevelEditor
	) override;
};

#undef LOCTEXT_NAMESPACE
