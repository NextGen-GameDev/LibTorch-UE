// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerCrossMapLrnOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerCrossMapLrnOptions"

/**
 * Options structure for the Cross Map LRN layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Cross Map LRN Layer Options")
struct ATUM_API FAtumLayerCrossMapLrnOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Number of neighbouring channels to normalise across
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 Size;
	
	/**
	 * Scaling factor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Alpha;
	
	/**
	 * Exponential factor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Beta;
	
	/**
	 * Offset to avoid division by 0
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 K;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerCrossMapLrnOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::CrossMapLRN2dOptions() const noexcept
	{ return torch::nn::CrossMapLRN2dOptions(Size).alpha(Alpha).beta(Beta).k(K); }
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::CrossMapLRN2dOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
