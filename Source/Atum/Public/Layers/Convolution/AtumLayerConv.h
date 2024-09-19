// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvOptions.h"
#include "IAtumLayerBaseConvolution.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/conv.h>
TORCH_INCLUDES_END

#include "AtumLayerConv.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConv"

/**
 * Base Convolution layer implementation
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Layer")
class ATUM_API UAtumLayerConv : public UObject, public IAtumLayerBaseConvolution
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerConvOptions)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerConvOptions Options;
	
	/**
	 * Checks if the dilated kernel is greater than the padded input
	 * 
	 * @param InputSizes Given input sizes
	 * @return Is the dilated kernel bigger than the padded input?
	 */
	[[nodiscard]]
	bool IsDilatedKernelGreaterThanPaddedInput(const TArray<int64>& InputSizes) const noexcept;
	
	/**
	 * Checks if the padding is greater than or equal to the input
	 * 
	 * @param InputSizes Given input sizes
	 * @return Is the padding bigger than or equal to the input sizes?
	 */
	[[nodiscard]]
	bool IsPaddingGreaterThanOrEqualToInput(const TArray<int64>& InputSizes) const noexcept;
	
	/**
	 * Checks if the padding causes multiple wrappings
	 * 
	 * @param InputSizes Given input sizes
	 * @return Does the padding cause multiple wrappings?
	 */
	[[nodiscard]]
	bool DoesPaddingCauseMultipleWrappings(const TArray<int64>& InputSizes) const noexcept;
	
	/**
	 * Function that runs when IAtumLayer::InitializeData is called
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the layer initialised?
	 */
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override;
	
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
	) override;
};


/**
 * 1D Convolution layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 1D Layer")
class ATUM_API UAtumLayerConv1D : public UAtumLayerConv
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::Conv1d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerConv1D() noexcept;
	
protected:
	/**
	 * Loads the layer data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};


/**
 * 2D Convolution layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 2D Layer")
class ATUM_API UAtumLayerConv2D : public UAtumLayerConv
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::Conv2d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerConv2D() noexcept;
	
protected:
	/**
	 * Loads the layer data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};


/**
 * 3D Convolution layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 3D Layer")
class ATUM_API UAtumLayerConv3D : public UAtumLayerConv
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::Conv3d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerConv3D() noexcept;
	
protected:
	/**
	 * Loads the layer data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
};

#undef LOCTEXT_NAMESPACE
