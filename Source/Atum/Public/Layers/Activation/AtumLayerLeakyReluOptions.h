// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/activation.h>
TORCH_INCLUDES_END

#include "AtumLayerLeakyReluOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLeakyReluOptions"

/**
 * Options structure for the Leaky ReLU layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Leaky ReLU Layer Options")
struct ATUM_API FAtumLayerLeakyReluOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Angle of the negative slope for negative inputs
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double NegativeSlope;
	
	/**
	 * Determines if the operation should be done on the spot
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bInplace;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerLeakyReluOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::LeakyReLUOptions() const noexcept
	{ return torch::nn::LeakyReLUOptions().negative_slope(NegativeSlope).inplace(bInplace); }
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::LeakyReLUOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
