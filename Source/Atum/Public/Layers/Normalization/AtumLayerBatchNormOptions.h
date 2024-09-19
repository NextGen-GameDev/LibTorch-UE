// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/batchnorm.h>
TORCH_INCLUDES_END

#include "AtumLayerBatchNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerBatchNormOptions"

/**
 * Options structure for the Batch Normalisation layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Batch Norm Layer Options")
struct ATUM_API FAtumLayerBatchNormOptions : public FAtumLayerBaseOptions
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
	FAtumLayerBatchNormOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::BatchNormOptions() const noexcept
	{
		return torch::nn::BatchNormOptions(NumFeatures)
		.eps(Eps)
		.momentum(Momentum == 0.0 ? c10::nullopt : c10::optional<double>(Momentum))
		.affine(bAffine)
		.track_running_stats(bTrackRunningStats);
	}
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::BatchNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
