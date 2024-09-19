// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerLayerNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLayerNormOptions"

/**
 * Options structure for the Layer Normalisation layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Layer Norm Layer Options")
struct ATUM_API FAtumLayerLayerNormOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Input shape
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> NormalizedShape;
	
	/**
	 * Smoothing term for stability
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	/**
	 * Determines if the layer has learnable per-element affine parameters
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bElementwiseAffine;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerLayerNormOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	explicit operator torch::nn::LayerNormOptions() const noexcept;
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::LayerNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
