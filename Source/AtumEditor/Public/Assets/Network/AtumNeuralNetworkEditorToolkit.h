// © 2023 Kaya Adrian.

#pragma once

#include "Toolkits/AssetEditorToolkit.h"

class UAtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkEditorToolkit"

/**
 * Asset editor toolkit for neural networks
 */
class ATUMEDITOR_API FAtumNeuralNetworkEditorToolkit : public FAssetEditorToolkit, public FGCObject
{
	/**
	 * The neural network that's being edited
	 */
	UAtumNeuralNetwork* NeuralNetwork;
	
	/**
	 * Handle to a delegated function that's called after compiling the class default object
	 */
	FDelegateHandle OnPostCDOCompiledHandle;
	
public:
	/**
	 * Unique identifier for this toolkit
	 */
	static const FName AtumNeuralNetworkAppIdentifier;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumNeuralNetworkEditorToolkit() noexcept;
	
	/**
	 * Initialises the actual asset editor
	 * 
	 * @param Mode Method in which the toolkit should be spawned
	 * @param InitToolkitHost Host of the editor window
	 * @param NetworkToEdit Object that should be opened for edit
	 */
	void InitEditor(
		EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost,
		UAtumNeuralNetwork* NetworkToEdit
	) noexcept;
	
	/**
	 * Registers objects that can create new tabs in the editor
	 * 
	 * @param InTabManager Manager that deals with the tabs themselves
	 */
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	/**
	 * Unregisters objects that can create new tabs in the editor
	 * 
	 * @param InTabManager Manager that deals with the tabs themselves
	 */
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	/**
	 * Gets the toolkit's identifier
	 * 
	 * @return Unique identifier of the toolkit
	 */
	[[nodiscard]]
	virtual FName GetToolkitFName() const override;
	
	/**
	 * Gets the base toolkit's name
	 * 
	 * @return Localisable base toolkit name
	 */
	[[nodiscard]]
	virtual FText GetBaseToolkitName() const override;
	
	/**
	 * Gets the toolkit's name
	 * 
	 * @return Localisable toolkit name
	 */
	[[nodiscard]]
	virtual FText GetToolkitName() const override;
	
	/**
	 * Gets the toolkit's tab prefix
	 * 
	 * @return Prefixed text of the tab's title
	 */
	[[nodiscard]]
	virtual FString GetWorldCentricTabPrefix() const override;
	
	/**
	 * Gets the toolkit's tab colour scale
	 * 
	 * @return Linear colour scale
	 */
	[[nodiscard]]
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	
	/**
	 * Adds the neural network to the garbage collector
	 * 
	 * @param Collector Collection of references to disposable objects
	 */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	
	/**
	 * Gets the edited object's name
	 * 
	 * @return The network's name
	 */
	[[nodiscard]]
	virtual FString GetReferencerName() const override;
	
	/**
	 * Closes the asset's editor window
	 * 
	 * @return Was the window closed successfully?
	 */
	virtual bool CloseWindow() override;
};

#undef LOCTEXT_NAMESPACE
