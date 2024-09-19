// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerGroupNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerGroupNormOptions"

/**
 * Options structure for the Group Normalisation layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Group Norm Layer Options")
struct ATUM_API FAtumLayerGroupNormOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Number of groups
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 NumGroups;
	
	/**
	 * Number of input channels
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 NumChannels;
	
	/**
	 * Smoothing term for stability
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	/**
	 * Determines if the layer has learnable affine parameters
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bAffine;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerGroupNormOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::GroupNormOptions() const noexcept
	{ return torch::nn::GroupNormOptions(NumGroups, NumChannels).eps(Eps).affine(bAffine); }
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::GroupNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
