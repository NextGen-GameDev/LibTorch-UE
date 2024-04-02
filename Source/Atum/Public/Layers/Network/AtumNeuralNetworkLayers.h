// © 2023 Kaya Adrian.

#pragma once

#include "Engine/DataAsset.h"

#include "AtumNeuralNetworkLayers.generated.h"

class UAtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkLayers"

/**
 * Data asset containing a list of layers and their data
 */
UCLASS(BlueprintType, EditInlineNew, DisplayName = "ATUM Neural Network Layers Data Asset")
class ATUM_API UAtumNeuralNetworkLayers : public UDataAsset
{
	GENERATED_BODY()

	friend class FAtumNeuralNetworkLayersCustomization;
	
#if WITH_EDITORONLY_DATA
	/**
	 * Cache of indices where a certain type of layer can be found in the list
	 */
	mutable TMap<TObjectPtr<const UClass>, TTuple<TArray<int32>, int32>> CachedIndices;
	
	/**
	 * Layer types before making a change in the editor
	 */
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<TObjectPtr<const UClass>> PreEditLayerTypes;
	
	/**
	 * Layer objects before making a change in the editor
	 */
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<TObjectPtr<UObject>> PreEditLayerObjects;
#endif
	
	/**
	 * List of constant layer types
	 */
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<const UClass*> LayerTypesConst;
	
	/**
	 * List of constant layer objects
	 */
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<const UObject*> LayerObjectsConst;
	
protected:
	/**
	 * List of layer types
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter = "GetLayerTypes", meta = (
		AllowPrivateAccess,
		MustImplement = "/Script/Atum.AtumLayer"
	))
	TArray<TObjectPtr<const UClass>> LayerTypes;
	
	/**
	 * List of layer objects
	 */
	UPROPERTY(Instanced, EditFixedSize, VisibleAnywhere, BlueprintGetter = "GetLayerObjects", meta = (
		AllowPrivateAccess
	))
	TArray<TObjectPtr<UObject>> LayerObjects;
	
public:
	/**
	 * Gets the layer types as constants to prevent making changes
	 * 
	 * @return The constant layer types
	 */
	UFUNCTION(BlueprintGetter, Category = "ATUM|Network", CustomThunk, meta = (Keywords = "ATUM Get Layer Types"))
	const TArray<const UClass*>& GetLayerTypes() const noexcept;
	
	/**
	 * Gets the layer objects as constants to prevent making changes
	 * 
	 * @return The constant layer objects
	 */
	UFUNCTION(BlueprintGetter, Category = "ATUM|Network", CustomThunk, meta = (Keywords = "ATUM Get Layer Objects"))
	const TArray<const UObject*>& GetLayerObjects() const noexcept;
	
protected:
#if WITH_EDITOR
	/**
	 * Event called before editing a property
	 * 
	 * @param PropertyAboutToChange Property which will suffer a change
	 */
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	
	/**
	 * Event called after editing a property
	 * @param PropertyChangedEvent Object holding information about which properties have been changed
	 */
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
	/**
	 * Caches the layer type indices whenever the layer types are being affected
	 */
	void OnLayerTypesPropertyChange_SetCachedNetworkIndices() noexcept;
	
	/**
	 * Event called when modifying a layer type
	 * 
	 * @param Index Layer position
	 */
	void OnLayerTypesPropertyChange_ValueSet(int32 Index) noexcept;
	
	/**
	 * Event called when moving a layer type
	 */
	void OnLayerTypesPropertyChange_ArrayMove() noexcept;
#endif
	
private:
	DECLARE_FUNCTION(execGetLayerTypes) noexcept;
	DECLARE_FUNCTION(execGetLayerObjects) noexcept;
	
	friend UAtumNeuralNetwork;
};

#undef LOCTEXT_NAMESPACE
