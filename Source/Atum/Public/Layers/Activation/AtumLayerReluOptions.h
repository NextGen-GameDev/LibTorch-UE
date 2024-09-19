// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/activation.h>
TORCH_INCLUDES_END

#include "AtumLayerReluOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerReluOptions"

/**
 * Options structure for the ReLU layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM ReLU Layer Options")
struct ATUM_API FAtumLayerReluOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Determines if the operation should be done on the spot
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bInplace;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerReluOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::ReLUOptions() const noexcept { return torch::nn::ReLUOptions(bInplace); }
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	FORCEINLINE void SetFrom(const torch::nn::ReLUOptions& Options) noexcept { bInplace = Options.inplace(); }
};

#undef LOCTEXT_NAMESPACE
