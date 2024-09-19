// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/normalization.h>
TORCH_INCLUDES_END

#include "AtumLayerLocalResponseNormOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLocalResponseNormOptions"

/**
 * Options structure for the Local Response Normalisation layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Local Response Norm Layer Options")
struct ATUM_API FAtumLayerLocalResponseNormOptions : public FAtumLayerBaseOptions
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
	double K;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerLocalResponseNormOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::LocalResponseNormOptions() const noexcept
	{ return torch::nn::LocalResponseNormOptions(Size).alpha(Alpha).beta(Beta).k(K); }
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::LocalResponseNormOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
