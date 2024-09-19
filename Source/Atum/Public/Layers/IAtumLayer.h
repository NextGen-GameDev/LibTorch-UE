// © 2023 Kaya Adrian.

#pragma once

#include <string>

#include "Serializable/IAtumSerializable.h"

#include <vector>

#include "IAtumLayer.generated.h"

class IAtumTensor;
enum class EAtumTensorDeviceType : uint8;
struct FAtumLayerBaseOptions;

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	class Module;
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


#define LOCTEXT_NAMESPACE "IAtumLayer"

/**
 * Interface object class used by the engine
 */
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Layer")
class UAtumLayer : public UAtumSerializable
{
	GENERATED_BODY()
};

/**
 * Network layer interface for creating deep learning operations
 */
class ATUM_API IAtumLayer : public IAtumSerializable
{
	GENERATED_BODY()
	
protected:
	/**
	 * Used to check if the optimiser has already been initialised or not
	 */
	bool bInitialized;
	
	/**
	 * Used for layers with dimensional variants to determine the size
	 */
	uint64 DimensionCount;
	
	/**
	 * Used for layers with dimensional variants to determine what size inputs are accepted
	 */
	std::vector<int64> ValidInputSizes;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	IAtumLayer() noexcept;



	/**
	 * Initialises the layer based on its options only once
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the layer initialised?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool InitializeData(bool bRetry = true);
	
	/**
	 * Forwards a tensor through this layer's operations
	 * 
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool Forward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	
	/**
	 * Creates a new layer and copies the data over from the original
	 * 
	 * @param OutClone Cloned layer
	 * @param Outer Clone's outer object
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	void CloneData(TScriptInterface<IAtumLayer>& OutClone, UObject* Outer = nullptr) const;
	
	/**
	 * Sets the layer's gradient to zero
	 * 
	 * @param bSetToNone Should the gradients be set to none instead?
	 * @return Was the operation successful?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool SetGradientToZero(bool bSetToNone = true);
	
	/**
	 * Gets this layer's current parameters
	 *
	 * @param Class Type of tensor implementation to use
	 * @param OutValues Array of all parameters
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	void GetParameters(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
	) const;
	
	/**
	 * Moves the layer to another device
	 * 
	 * @param Value Device
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	void SetDeviceType(EAtumTensorDeviceType Value);
	
	/**
	 * Getter for Module as its base class
	 */
	[[nodiscard]]
	virtual const torch::nn::Module* GetBaseModule() const noexcept;
	
	/**
	 * Getter for Module as its base class
	 */
	[[nodiscard]]
	FORCEINLINE torch::nn::Module* GetBaseModule() noexcept
	{ return const_cast<torch::nn::Module*>(std::as_const(*this).GetBaseModule()); }
	
	/**
	 * Getter for Options as its base class
	 */
	[[nodiscard]]
	virtual const FAtumLayerBaseOptions* GetBaseLayerOptions() const noexcept;
	
	/**
	 * Getter for Options as its base class
	 */
	[[nodiscard]]
	virtual FAtumLayerBaseOptions* GetBaseLayerOptions() noexcept;
	
	/**
	 * Forwards a tensor through this layer's operations by overloading the () operator
	 * 
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */
	FORCEINLINE bool operator()(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept
	{ return Execute_Forward(_getUObject(), Input, Output); }
	
protected:
	/**
	 * Checks if the given input size is acceptable for this layer
	 * 
	 * @param InputSizeCount Input size to check
	 * @return Is the input size valid?
	 */
	[[nodiscard]]
	bool AreInputSizesValid(int32 InputSizeCount) const noexcept;
	
	/**
	 * Checks if the given input sizes are acceptable for this layer
	 * 
	 * @param InputSizes Array of input sizes to check
	 * @param ExpectedChannels How many channels are expected as input
	 * @return Are all input sizes valid?
	 */
	[[nodiscard]]
	bool AreInputSizesValid(const TArray<int64>& InputSizes, int64 ExpectedChannels) const noexcept;
	
	/**
	 * Function that runs when IAtumLayer::InitializeData is called
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the layer initialised?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnInitializeData(bool bRetry = true);
	
	/**
	 * Function that runs when IAtumLayer::Forward is called
	 * 
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnForward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	
	/**
	 * Function that runs when IAtumLayer::InitializeData is called
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the layer initialised?
	 */
	virtual bool OnInitializeData_Implementation(bool bRetry = true);
	
	/**
	 * Function that runs when IAtumLayer::Forward is called
	 * 
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	);
	
	/**
	 * Creates a new layer and copies the data over from the original
	 * 
	 * @param OutClone Cloned layer
	 * @param Outer Clone's outer object
	 */
	virtual void CloneData_Implementation(
		TScriptInterface<IAtumLayer>& OutClone,
		UObject* Outer = nullptr
	) const noexcept;
	
	/**
	 * Sets the layer's gradient to zero
	 * 
	 * @param bSetToNone Should the gradients be set to none instead?
	 * @return Was the operation successful?
	 */
	virtual bool SetGradientToZero_Implementation(bool bSetToNone = true) noexcept;
	
	/**
	 * Gets this layer's current parameters
	 *
	 * @param Class Type of tensor implementation to use
	 * @param OutValues Array of all parameters
	 */
	virtual void GetParameters_Implementation(
		const UClass* Class,
		TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
	) const noexcept;
	
	/**
	 * Moves the layer to another device
	 * 
	 * @param Value Device
	 */
	virtual void SetDeviceType_Implementation(EAtumTensorDeviceType Value) noexcept;
	
	/**
	 * Sets the layer's module using a base module
	 * 
	 * @param Value Pointer to base module
	 */
	virtual void SetBaseModule(const torch::nn::Module* Value) noexcept;
	
	/**
	 * Saves the layer data to a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool SaveToFile_Implementation(const FString& RelativePath) const override;
	
	/**
	 * Loads the layer data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
	
private:
	/**
	 * Initialises the layer based on its options only once
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the layer initialised?
	 */
	bool InitializeData_Implementation(bool bRetry = true) noexcept;
	
	/**
	 * Forwards a tensor through this layer's operations
	 * 
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */
	bool Forward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept;
	
public:
	/**
	 * Getter for bInitialized
	 */
	[[nodiscard]]
	FORCEINLINE bool IsInitialized() const noexcept { return bInitialized; }
	
	/**
	 * Getter for DimensionCount
	 */
	[[nodiscard]]
	FORCEINLINE uint64 GetDimensionCount() const noexcept { return DimensionCount; }
	
	/**
	 * Getter for ValidInputSizes
	 */
	[[nodiscard]]
	FORCEINLINE const std::vector<int64>& GetValidInputSizes() const noexcept { return ValidInputSizes; }
};

#undef LOCTEXT_NAMESPACE
