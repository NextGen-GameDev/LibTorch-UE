// © 2023 Kaya Adrian.

#pragma once

#include "AtumNeuralNetworkOptions.h"
#include "Layers/IAtumLayer.h"
#include "Macros/AtumMacrosGuards.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/cloneable.h>
TORCH_INCLUDES_END

#include "AtumNeuralNetwork.generated.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	/**
	 * LibTorch implementation of a custom network as a cloneable module
	 */
	class AtumNetworkImpl : public Cloneable<AtumNetworkImpl>
	{
	public:
		/**
		 * Structure containing this instance's options
		 */
		AtumNetworkOptions options;
		
		/**
		 * Constructor
		 */
		UE_NODISCARD_CTOR
		explicit AtumNetworkImpl(const AtumNetworkOptions& options_ = {}) noexcept;
		
		/**
		 * Forwards a tensor through this module's operations
		 * 
		 * @param input Tensor to operate on
		 * @return The resulting tensor
		 */
		[[nodiscard]]
		// ReSharper disable once CppMemberFunctionMayBeStatic
		FORCEINLINE Tensor forward(const Tensor& input) { return input; }
		
		/**
		 * Resets the module's options to their default values
		 */
		virtual void reset() override;
		
		/**
		 * Prints the module's name
		 * 
		 * @param stream Where to print the string
		 */
		virtual void pretty_print(std::ostream& stream) const override;
	};
	
	TORCH_MODULE(AtumNetwork);
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


/**
 * Neural network class as a layer implementation
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew, DisplayName = "ATUM Neural Network")
class ATUM_API UAtumNeuralNetwork : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumNeuralNetworkOptions, torch::nn::AtumNetwork)
	
#if WITH_EDITOR
	DECLARE_MULTICAST_DELEGATE(FOnPostCDOCompiled);
#endif
	
	/**
	 * Cache of the constant registered layers after initialisation
	 */
	UPROPERTY(Transient, NonTransactional)
	mutable TArray<const UObject*> RegisteredLayersConst;
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumNeuralNetworkOptions Options;
	
	/**
	 * Array of registered layers after initialisation
	 */
	UPROPERTY(Transient, NonTransactional, VisibleAnywhere, BlueprintGetter = "GetRegisteredLayers", meta = (
		AllowPrivateAccess
	))
	TArray<TObjectPtr<UObject>> RegisteredLayers;
	
public:
#if WITH_EDITOR
	/**
	 * Pointer to a delegated function that's called after compiling the class default object
	 */
	static const TUniquePtr<FOnPostCDOCompiled> OnPostCDOCompiled;
#endif
	
	/**
	 * Registers a layer with this network
	 * 
	 * @param Layer Layer to register
	 * @return Was the layer registered successfully?
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network", meta = (Keywords = "ATUM Register Layer"))
	FORCEINLINE bool RegisterLayer(const TScriptInterface<IAtumLayer>& Layer) noexcept
	{ return RegisterLayerAt(Layer, RegisteredLayers.Num()); }
	
	/**
	 * Registers a layer with this network at a certain place
	 * 
	 * @param Layer Layer to register
	 * @param Index Position where to place the layer
	 * @return Was the layer registered successfully?
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network", meta = (Keywords = "ATUM Register Layer At Index"))
	bool RegisterLayerAt(const TScriptInterface<IAtumLayer>& Layer, int32 Index = 0) noexcept;
	
	/**
	 * Gets the registered layers as constants to prevent making changes
	 * 
	 * @return The constant registered layers
	 */
	UFUNCTION(BlueprintGetter, Category = "ATUM|Network", CustomThunk, meta = (Keywords = "ATUM Get Registered Layers"))
	const TArray<const UObject*>& GetRegisteredLayers() const noexcept;
	
protected:
	/**
	 * Gets this network's current parameters from every layer
	 *
	 * @param Class Type of tensor implementation to use
	 * @param OutValues Array of all parameters
	 */
	virtual void GetParameters_Implementation(
		const UClass* Class,
		TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
	) const noexcept override;
	
	/**
	 * Moves the entire network to another device
	 * 
	 * @param Value Device
	 */
	virtual void SetDeviceType_Implementation(EAtumTensorDeviceType Value) noexcept override;
	
	/**
	 * Saves the entire network's data to a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool SaveToFile_Implementation(const FString& RelativePath) const override;
	
#if WITH_EDITOR
	/**
	 * Broadcasts that the class default object has just compiled
	 * 
	 * @param Context Object holding context information
	 */
	virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;
#endif
	
private:
#if WITH_EDITOR
	/**
	 * Editor function to call UAtumNeuralNetwork::InitializeData
	 */
	UFUNCTION(CallInEditor, BlueprintInternalUseOnly, Category = "ATUM|Network")
	void InitializeAssetData() noexcept;
#endif
	
	DECLARE_FUNCTION(execGetRegisteredLayers) noexcept;
};

#undef LOCTEXT_NAMESPACE
