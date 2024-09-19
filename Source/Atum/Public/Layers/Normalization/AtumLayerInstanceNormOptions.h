// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/functional/instancenorm.h>
TORCH_INCLUDES_END

#include "AtumLayerInstanceNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerInstanceNormOptions"

/**
 * Options structure for the Instance Normalisation layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Instance Norm Layer Options")
struct ATUM_API FAtumLayerInstanceNormOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Number of input features
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 NumFeatures;
	
	/**
	 * Smoothing term for stability
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	/**
	 * Used to compute the running mean and variance
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Momentum;
	
	/**
	 * Determines if the layer has learnable affine parameters
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bAffine;
	
	/**
	 * Controls whether or not to track the running mean and variance
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bTrackRunningStats;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerInstanceNormOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::InstanceNormOptions() const noexcept
	{
		return torch::nn::InstanceNormOptions(NumFeatures)
		.eps(Eps)
		.momentum(Momentum)
		.affine(bAffine)
		.track_running_stats(bTrackRunningStats);
	}
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::InstanceNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
