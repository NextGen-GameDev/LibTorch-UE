// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvTransposeOptions.h"
#include "IAtumLayerBaseConvolution.h"
#include "Macros/AtumMacrosLayer.h"

TORCH_INCLUDES_START
#include <torch/nn/modules/conv.h>
TORCH_INCLUDES_END

#include "AtumLayerConvTranspose.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvTranspose"

/**
 * Base Convolutional Transpose layer implementation
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose Layer")
class ATUM_API UAtumLayerConvTranspose : public UObject, public IAtumLayerBaseConvolution
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(FAtumLayerConvTransposeOptions)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLayerConvTransposeOptions Options;
	
	/**
	 * Checks if the computed output tensor's size is valid
	 * 
	 * @param InputSizes Given input sizes
	 * @return Is the calculated output tensor size valid?
	 */
	[[nodiscard]]
	bool IsCalculatedOutputTensorSizeValid(const TArray<int64>& InputSizes) const noexcept;
	
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
 * 1D Convolutional Transpose layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 1D Layer")
class ATUM_API UAtumLayerConvTranspose1D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::ConvTranspose1d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose1D() noexcept;
	
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
 * 2D Convolutional Transpose layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 2D Layer")
class ATUM_API UAtumLayerConvTranspose2D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::ConvTranspose2d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose2D() noexcept;
	
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
 * 3D Convolutional Transpose layer implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 3D Layer")
class ATUM_API UAtumLayerConvTranspose3D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER_MODULE_ONLY(torch::nn::ConvTranspose3d)
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose3D() noexcept;
	
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
