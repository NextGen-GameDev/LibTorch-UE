// © 2023 Kaya Adrian.

#pragma once

#include "AtumSettingsBase.h"

#include "AtumSettingsEditor.generated.h"


#define LOCTEXT_NAMESPACE "AtumSettingsEditor"

/**
 * ATUM settings that control editor features
 */
UCLASS(MinimalAPI, BlueprintType, DisplayName = "ATUM Editor Settings")
class UAtumSettingsEditor : public UAtumSettingsBase
{
	GENERATED_BODY()
	
protected:
	/**
	 * Controls if the ATUM editor module can output logs to the console
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, DisplayName = "Enable LogAtumEditor", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Editor.EnableLogAtumEditor"
	))
	bool bLogAtumEditorEnabled;
	
	/**
	 * Controls if Blueprintable classes can be used as a base when creating a neural network asset
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, DisplayName = "Allow Blueprintable Classes", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Editor.AllowBlueprintableClasses"
	))
	bool bBlueprintableClassesAllowed;
	
	/**
	 * The colour to use for neural network assets in the editor
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta = (
		AllowPrivateAccess,
		ConfigRestartRequired = "true"
	))
	FColor NeuralNetworkAssetTypeColor;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumSettingsEditor() noexcept;
	
#if WITH_EDITOR
	/**
	 * Gets the section name of these settings
	 * 
	 * @return Localisable section text
	 */
	[[nodiscard]]
	virtual FText GetSectionText() const override;
	
	/**
	 * Gets the description of the section
	 * 
	 * @return Localisable section description
	 */
	[[nodiscard]]
	virtual FText GetSectionDescription() const override;
#endif
	
	/**
	 * Getter for bLogAtumEditorEnabled
	 */
	[[nodiscard]]
	FORCEINLINE bool IsLogAtumEditorEnabled() const noexcept { return bLogAtumEditorEnabled; }
	
	/**
	 * Setter for bLogAtumEditorEnabled
	 */
	[[nodiscard]]
	FORCEINLINE void SetLogAtumEditorEnabled(const bool bValue) noexcept { bLogAtumEditorEnabled = bValue; }
	
	/**
	 * Getter for bBlueprintableClassesAllowed
	 */
	[[nodiscard]]
	FORCEINLINE bool AreBlueprintableClassesAllowed() const noexcept { return bBlueprintableClassesAllowed; }
	
	/**
	 * Setter for bBlueprintableClassesAllowed
	 */
	[[nodiscard]]
	FORCEINLINE void SetBlueprintableClassesAllowed(const bool bValue) noexcept
	{ bBlueprintableClassesAllowed = bValue; }
	
	/**
	 * Getter for NeuralNetworkAssetTypeColor
	 */
	[[nodiscard]]
	FORCEINLINE FColor GetNeuralNetworkAssetTypeColor() const noexcept { return NeuralNetworkAssetTypeColor; }
};

#undef LOCTEXT_NAMESPACE
